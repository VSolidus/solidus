// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Bitcoin Core developers
// Copyright (c) 2021 VSolidus Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "NY Times 02/Sep/2021 Record Rainfall Swamps Roads and Strands Travelers";
    const CScript genesisOutputScript = CScript() << ParseHex("988301e1497e77a8069e2f151a8c1be311eb366bb204baa47938e2e6e67a258c2c57dfaaf40d7897abf229ab43921ad610e9ff082130c98318aa4aad2f52dd9af1") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 2172480;
		/*
        consensus.BIP34Height = 710000;
        consensus.BIP34Hash = uint256S("fa09d204a83a768ed5a7c8d441fa62f2043abf420cff1226c7b4329aeb9d51cf");
        consensus.BIP65Height = 918684; // bab3041e8977e0dc3eeff63fe707b92bde1dd449d8efafb248c27c8264cc311a
        consensus.BIP66Height = 811879; // 7aceee012833fa8952f8835d8b1b3ae233cd6ab08fdb27a771d2bd7bdc491894
		*/
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 5 * 60;
        consensus.nPowTargetSpacing = 1 * 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6048; // 75% of 8064
        consensus.nMinerConfirmationWindow = 8064; // nPowTargetTimespan / nPowTargetSpacing * 4
		/*
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000006805c7318ce2736c0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x1673fa904a93848eca83d5ca82c7af974511a7e640e22edc2976420744f2e56a"); //1155631
		*/

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa6;
        pchMessageStart[1] = 0x7b;
        pchMessageStart[2] = 0xa8;
        pchMessageStart[3] = 0xd9;
        nDefaultPort = 44474;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1630587125, 2002481657, 0x1e0ffff0, 1, 300 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
		assert(genesis.hashMerkleRoot == uint256S("0x84721d8da9deb2e370f20f8c1bf21df87f9a2ad1db3fb3dff7e68e3bc355f295"));
        assert(consensus.hashGenesisBlock == uint256S("0x862b37af3035f184aadd5f02d0c1bcd678a8e9bd834cd1ecb17782bd1e3dc44b"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("213.171.213.15", "213.171.213.15", true));
        vSeeds.push_back(CDNSSeedData("77.68.74.226", "77.68.74.226", true));
        vSeeds.push_back(CDNSSeedData("185.132.40.137", "185.132.40.137", true));
        vSeeds.push_back(CDNSSeedData("77.68.91.233", "77.68.91.233", true));
        vSeeds.push_back(CDNSSeedData("185.132.40.230", "185.132.40.230", true));
        vSeeds.push_back(CDNSSeedData("34.243.30.207", "34.243.30.207", true));
        vSeeds.push_back(CDNSSeedData("34.245.23.85", "34.245.23.85", true));
        vSeeds.push_back(CDNSSeedData("52.30.102.233", "52.30.102.233", true));
        vSeeds.push_back(CDNSSeedData("3.10.58.157", "3.10.58.157", true));
        vSeeds.push_back(CDNSSeedData("3.8.149.136", "3.8.149.136", true));
        vSeeds.push_back(CDNSSeedData("18.132.68.97", "18.132.68.97", true));
        vSeeds.push_back(CDNSSeedData("77.68.88.65", "77.68.88.65", true));
        vSeeds.push_back(CDNSSeedData("35.177.153.30", "35.177.153.30", true));
        vSeeds.push_back(CDNSSeedData("18.130.228.72", "18.130.228.72", true));
        vSeeds.push_back(CDNSSeedData("34.238.150.23", "34.238.150.23", true));
        vSeeds.push_back(CDNSSeedData("54.174.27.209", "54.174.27.209", true));
        vSeeds.push_back(CDNSSeedData("3.84.172.27", "3.84.172.27", true));
        vSeeds.push_back(CDNSSeedData("3.239.103.153", "3.239.103.153", true));
        vSeeds.push_back(CDNSSeedData("54.147.94.214", "54.147.94.214", true));
        vSeeds.push_back(CDNSSeedData("13.229.184.62", "13.229.184.62", true));
        vSeeds.push_back(CDNSSeedData("13.213.68.163", "13.213.68.163", true));
        vSeeds.push_back(CDNSSeedData("3.8.149.136", "3.8.149.136", true));
        vSeeds.push_back(CDNSSeedData("18.142.95.163", "18.142.95.163", true));
        vSeeds.push_back(CDNSSeedData("185.132.38.57", "185.132.38.57", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,50);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,176);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0x862b37af3035f184aadd5f02d0c1bcd678a8e9bd834cd1ecb17782bd1e3dc44b"))
        };

        chainTxData = ChainTxData{
            // Data as of block b44bc5ae41d1be67227ba9ad875d7268aa86c965b1d64b47c35be6e8d5c352f4 (height 1155626).
            1630587125, // * UNIX timestamp of last known number of transactions
            0,  // * total number of transactions between genesis and that timestamp
                    //   (the tx=... number in the SetBestChain debug.log lines)
            0.0     // * estimated number of transactions per second after that timestamp
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 2172480;
		/*
        consensus.BIP34Height = 76;
        consensus.BIP34Hash = uint256S("8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573");
        consensus.BIP65Height = 76; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.BIP66Height = 76; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
		*/
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 5 * 60;
        consensus.nPowTargetSpacing = 1 * 30;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
		/*
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000000054cb9e7a0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x43a16a626ef2ffdbe928f2bc26dcd5475c6a1a04f9542dfc6a0a88e5fcf9bd4c"); //8711
		*/

        pchMessageStart[0] = 0x5d;
        pchMessageStart[1] = 0xd7;
        pchMessageStart[2] = 0x68;
        pchMessageStart[3] = 0xf8;
        nDefaultPort = 44475;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1630587125, 1500445, 0x1e0ffff0, 1, 300 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
		assert(genesis.hashMerkleRoot == uint256S("0x84721d8da9deb2e370f20f8c1bf21df87f9a2ad1db3fb3dff7e68e3bc355f295"));
        assert(consensus.hashGenesisBlock == uint256S("0x18a9a2b70e28e4f34665530a53469c2249d696052e876f5892ad6c3e24f00ca7"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("213.171.213.15", "213.171.213.15", true));
        vSeeds.push_back(CDNSSeedData("77.68.74.226", "77.68.74.226", true));
        vSeeds.push_back(CDNSSeedData("185.132.40.137", "185.132.40.137", true));
        vSeeds.push_back(CDNSSeedData("77.68.91.233", "77.68.91.233", true));
        vSeeds.push_back(CDNSSeedData("185.132.40.230", "185.132.40.230", true));
        vSeeds.push_back(CDNSSeedData("34.243.30.207", "34.243.30.207", true));
        vSeeds.push_back(CDNSSeedData("34.245.23.85", "34.245.23.85", true));
        vSeeds.push_back(CDNSSeedData("52.30.102.233", "52.30.102.233", true));
        vSeeds.push_back(CDNSSeedData("3.10.58.157", "3.10.58.157", true));
        vSeeds.push_back(CDNSSeedData("3.8.149.136", "3.8.149.136", true));
        vSeeds.push_back(CDNSSeedData("18.132.68.97", "18.132.68.97", true));
        vSeeds.push_back(CDNSSeedData("77.68.88.65", "77.68.88.65", true));
        vSeeds.push_back(CDNSSeedData("35.177.153.30", "35.177.153.30", true));
        vSeeds.push_back(CDNSSeedData("18.130.228.72", "18.130.228.72", true));
        vSeeds.push_back(CDNSSeedData("34.238.150.23", "34.238.150.23", true));
        vSeeds.push_back(CDNSSeedData("54.174.27.209", "54.174.27.209", true));
        vSeeds.push_back(CDNSSeedData("3.84.172.27", "3.84.172.27", true));
        vSeeds.push_back(CDNSSeedData("3.239.103.153", "3.239.103.153", true));
        vSeeds.push_back(CDNSSeedData("54.147.94.214", "54.147.94.214", true));
        vSeeds.push_back(CDNSSeedData("13.229.184.62", "13.229.184.62", true));
        vSeeds.push_back(CDNSSeedData("13.213.68.163", "13.213.68.163", true));
        vSeeds.push_back(CDNSSeedData("3.8.149.136", "3.8.149.136", true));
        vSeeds.push_back(CDNSSeedData("18.142.95.163", "18.142.95.163", true));
        vSeeds.push_back(CDNSSeedData("185.132.38.57", "185.132.38.57", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x18a9a2b70e28e4f34665530a53469c2249d696052e876f5892ad6c3e24f00ca7")),
        };

        chainTxData = ChainTxData{
            // Data as of block f2dc531da6be01f53774f970aaaca200c7a8317ee9fd398ee733b40f14e265d1 (height 8702)
            1630587125,
            0,
            0.02265200874042768
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
		/*
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
		*/
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 5 * 60;
        consensus.nPowTargetSpacing = 1 * 30;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
		/*
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;
		*/

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xbb;
        pchMessageStart[2] = 0xbc;
        pchMessageStart[3] = 0xdd;
        nDefaultPort = 44476;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1630587125, 3, 0x207fffff, 1, 300 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
		assert(genesis.hashMerkleRoot == uint256S("0x84721d8da9deb2e370f20f8c1bf21df87f9a2ad1db3fb3dff7e68e3bc355f295"));
        assert(consensus.hashGenesisBlock == uint256S("0x06eaab51d7a580206a7feaeb983906837fbedaef8aee7fafcc32686755786107"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x06eaab51d7a580206a7feaeb983906837fbedaef8aee7fafcc32686755786107"))
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
