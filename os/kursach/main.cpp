#include <iostream>
#include <pcap.h>
#include <cstring>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

class PacketSniffer {
private:
    char errorBuffer[PCAP_ERRBUF_SIZE];
    pcap_t* handle;

public:
    PacketSniffer(const std::string& device) {
        handle = pcap_open_live(device.c_str(), BUFSIZ, 1, 1000, errorBuffer);
        if (!handle) {
            throw std::runtime_error("Could not open device: " + std::string(errorBuffer));
        }

        struct bpf_program filter;
        std::string filterExpression = "tcp";
        if (pcap_compile(handle, &filter, filterExpression.c_str(), 0, PCAP_NETMASK_UNKNOWN) == -1) {
            throw std::runtime_error("Could not compile filter: " + std::string(pcap_geterr(handle)));
        }
        if (pcap_setfilter(handle, &filter) == -1) {
            throw std::runtime_error("Could not set filter: " + std::string(pcap_geterr(handle)));
        }
    }

    ~PacketSniffer() {
        if (handle) {
            pcap_close(handle);
        }
    }

    void start() {
        std::cout << "Starting packet capture..." << std::endl;
        if (pcap_loop(handle, 0, packetHandler, nullptr) < 0) {
            throw std::runtime_error("Error in pcap_loop: " + std::string(pcap_geterr(handle)));
        }
    }

    static void packetHandler(u_char* args, const struct pcap_pkthdr* header, const u_char* packet) {
        const struct ether_header* ethernetHeader = reinterpret_cast<const struct ether_header*>(packet);

        if (ntohs(ethernetHeader->ether_type) != ETHERTYPE_IP) {
            return;
        }

        const struct ip* ipHeader = reinterpret_cast<const struct ip*>(packet + sizeof(struct ether_header));
        char srcIp[INET_ADDRSTRLEN];
        char destIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ipHeader->ip_src), srcIp, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ipHeader->ip_dst), destIp, INET_ADDRSTRLEN);

        std::cout << "Packet captured:" << std::endl;
        std::cout << "Source IP: " << srcIp << std::endl;
        std::cout << "Destination IP: " << destIp << std::endl;

        if (ipHeader->ip_p == IPPROTO_TCP) {
            const struct tcphdr* tcpHeader = reinterpret_cast<const struct tcphdr*>(packet + sizeof(struct ether_header) + ipHeader->ip_hl * 4);
            std::cout << "Protocol: TCP" << std::endl;
            std::cout << "Source Port: " << ntohs(tcpHeader->th_sport) << std::endl;
            std::cout << "Destination Port: " << ntohs(tcpHeader->th_dport) << std::endl;
        } else if (ipHeader->ip_p == IPPROTO_UDP) {
            const struct udphdr* udpHeader = reinterpret_cast<const struct udphdr*>(packet + sizeof(struct ether_header) + ipHeader->ip_hl * 4);
            std::cout << "Protocol: UDP" << std::endl;
            std::cout << "Source Port: " << ntohs(udpHeader->uh_sport) << std::endl;
            std::cout << "Destination Port: " << ntohs(udpHeader->uh_dport) << std::endl;
        } else {
            std::cout << "Protocol: Other (" << static_cast<int>(ipHeader->ip_p) << ")" << std::endl;
        }

        std::cout << "Packet length: " << header->len << " bytes" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
};

int main() {
    try {
        pcap_if_t* allDevices;
        char errorBuffer[PCAP_ERRBUF_SIZE];

        if (pcap_findalldevs(&allDevices, errorBuffer) == -1) {
            throw std::runtime_error("Could not find devices: " + std::string(errorBuffer));
        }

        std::cout << "Available devices:" << std::endl;
        int i = 0;
        for (pcap_if_t* device = allDevices; device; device = device->next) {
            std::cout << ++i << ". " << (device->name ? device->name : "Unknown") << std::endl;
        }

        if (i == 0) {
            throw std::runtime_error("No devices found.");
        }

        std::string device = allDevices->name;
        std::cout << "Using device: " << device << std::endl;

        pcap_freealldevs(allDevices);

        PacketSniffer sniffer(device);
        sniffer.start();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
