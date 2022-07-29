// Copyright (c) 2021 yanmaani
// Licensed under CC0 (Public domain)

#include <test/util/setup_common.h>
#include <key_io.h>
#include <wallet/rpc/names.h>

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(rpcnames_tests, RegTestingSetup) // Keys are in regtest format

static void
TestNameSalt(const std::string& privkey_b58, const std::string& name_str, const std::string& expectedSalt_hex) {
    const CKey privkey = DecodeSecret(privkey_b58);
    const valtype name(name_str.begin(), name_str.end());
    const valtype expectedSalt = ParseHex(expectedSalt_hex);

    valtype salt(20);
    wallet::getNameSalt(privkey, name, salt);

    BOOST_CHECK(salt == expectedSalt);
}

BOOST_AUTO_TEST_CASE(name_salts)
{
    SelectParams(CBaseChainParams::REGTEST);
    TestNameSalt( // test_name_salt_addr_p2pkh
                /* private key   */ "cQDxbmQfwRV3vP1mdnVHq37nJekHLsuD3wdSQseBRA2ct4MFk5Pq",
                /* name          */ "d/wikileaks",
                /* expected salt */ "c33f6d84c93d769da2a8882ed9d4a69e2052dd9a");
    TestNameSalt( // test_name_salt_addr_p2wpkh_p2sh
                /* private key   */ "cU9hVzhpvfn91u2zTVn8uqF2ymS7ucYH8V5TmsTDmuyMHgRk9WsJ",
                /* name          */ "d/wikileaks",
                /* expected salt */ "b14763659b268460865db01b2b10b80a9cbe9ceb");
    TestNameSalt( // test_name_salt_addr_p2wpkh
                /* private key   */ "cPuQzcNEgbeYZ5at9VdGkCwkPA9r34gvEVJjuoz384rTfYpahfe7",
                /* name          */ "d/wikileaks",
                /* expected salt */ "a39038cddfcc17d391b8620639a72178dc73b19a");
}

BOOST_AUTO_TEST_SUITE_END()
