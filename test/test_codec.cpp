#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <iomanip>
#include <c509_types.hpp>
#include <c509_codec.hpp>

using namespace C509;

TEST_CASE("sum1")
{
    Certificate cert = Certificate{
        TBSCertificate{
            .c509CertificateType = 3,
            .certificateSerialNumber = {bounded_array<uint8_t, MAX_CSN_BYTES>{{0xAA, 0xBB, 0xCC}, 3}}}};

    uint8_t out[1024];
    size_t out_size, out_size_decode;

    Certificate newCert = Certificate{};


    std::cout << encode(out, 1024, &cert, &out_size) << std::endl;

    std::cout << decode(out, out_size, &newCert, &out_size_decode) << std::endl;

    std::cout << out_size_decode << std::endl;
    std::cout <<  static_cast<int>(newCert.tbsCertificate.c509CertificateType) << " | " << newCert.tbsCertificate.certificateSerialNumber.bytes.len << std::endl;

    for (int i = 0; i < newCert.tbsCertificate.certificateSerialNumber.bytes.len; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(newCert.tbsCertificate.certificateSerialNumber.bytes.elements[i]) << " ";
    }
    
    std::cout << std :: endl;

    for (int i = 0; i < out_size; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(out[i]) << " ";
    }
}
