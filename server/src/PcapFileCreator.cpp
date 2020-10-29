//
// Created by tal on 10/29/20.
//

#include "PcapFileCreator.h"

void PcapFileCreator::createFileFromBytes(const char *name, const uint8_t *stream, size_t length) {
    FILE *pcap_file = fopen(name, "wb");
    fwrite(stream, 1, length, pcap_file);
    fclose(pcap_file);
}

long PcapFileCreator::getFileSize(const char *name) {
    struct stat stat_buf;
    int rc = stat(name, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

uint8_t *PcapFileCreator::createByteStreamFromFile(const char *name) {
    FILE *pcap_file = fopen(name, "rb");
    uint8_t *stream = nullptr;
    fread(stream, 1, getFileSize(name), pcap_file);
    return stream;
}