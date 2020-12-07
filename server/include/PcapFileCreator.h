//
// Created by tal on 10/29/20.
//

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

#ifndef SERVER_PCAPFILECREATOR_H
#define SERVER_PCAPFILECREATOR_H
typedef struct pcap_hdr_s {
    uint32_t magic_number;
    uint16_t version_major;
    uint16_t version_minor;
    uint32_t thiszone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t network;
} pcap_hdr_t;
typedef struct pcaprec_hdr_s {
    uint32_t ts_sec;
    uint32_t ts_usec;
    uint32_t incl_len;
    uint32_t orig_len;
} pcaprec_hdr_t;

class PcapFileCreator {
public:
    static long getFileSize(const char *fileName);

    static void createFileFromBytes(const char *fileName, char *buffer, long fileSize);

    static char *createByteStreamFromFile(const char *fileName, long fileSize);
};

#endif //SERVER_PCAPFILECREATOR_H
