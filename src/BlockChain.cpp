#include "BlockChain.h"

BlockChain::BlockChain(){
    constructGenesis();
}

Block BlockChain::constructGenesis(){
    constructBlock(0, "0");
}

Block BlockChain::constructBlock(const int& proofNum, const std::string& prevHash){
    time_t currentTime = std::time(0);
    double timeStamp = static_cast<double>(currentTime);
    
    Block block(chain.size(), proofNum, prevHash, currentData, timeStamp);

    currentData.clear(); // Clears transaction data for new blocks.

    chain.push_back(block);

    return block;
}

// TO DO, implement Proof of Work
bool BlockChain::checkValidity(Block& newBlock){
    if (newBlock.checkIndex() < lastBlock().checkIndex()){
        return false;
    } else if (newBlock.checkHash() != lastBlock().calculateHash()){
        return false;
    } else if (newBlock.checkTimeStamp() <= lastBlock().checkTimeStamp()){
        return false;
    } else {
        return true;
    }
}

Block BlockChain::lastBlock(){
    return chain.back(); // This returns a reference of the last Block Object
}