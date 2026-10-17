#include <gtest/gtest.h>
#include "../electra_remote_protocol.h"

// how to run:
// 1 cmake -S . -B build
// 2 cmake --build build
// 3 cd build && ctest

TEST(ElectraRemoteProtocol, DefaultSingal)
{
    ElectraRemoteProtocol::ElectraRemoteProtocol protocol;
    auto signal = protocol.get_signal();

    // we should get
    // 11000011 11100001 00000111 00000000 00000101 00000000 00000100 00000000 00000000 00000000 00000000 10100000 11101111 
    EXPECT_EQ(signal.size(), 13u);
    EXPECT_EQ(signal[0], 0b11000011);
    EXPECT_EQ(signal[1], 0b11100001);
    EXPECT_EQ(signal[2], 0b00000111);
    EXPECT_EQ(signal[3], 0b00000000);
    EXPECT_EQ(signal[4], 0b00000101);
    EXPECT_EQ(signal[5], 0b00000000);
    EXPECT_EQ(signal[6], 0b00000100);
    EXPECT_EQ(signal[7], 0b00000000);
    EXPECT_EQ(signal[8], 0b00000000);
    EXPECT_EQ(signal[9], 0b00000000);
    EXPECT_EQ(signal[10], 0b00000000);
    EXPECT_EQ(signal[11], 0b10100000);
    EXPECT_EQ(signal[12], 0b11101111);

}
