#include "BlockChain.h"

BlockChain::BlockChain(){
    constructGenesis();
}

void BlockChain::constructGenesis(){
    constructBlock(0, "0");
}

Block BlockChain::constructBlock(const int& proofNum, const std::string& prevHash){
    time_t currentTime = time(0);
    double timeStamp = static_cast<double>(currentTime);
    
    Block block(chain.size(), proofNum, prevHash, currentData, timeStamp);

    currentData.clear(); // Clears transaction data for new blocks.

    chain.push_back(block);

    return block;
}

bool BlockChain::checkValidity(Block& newBlock){
    if (newBlock.checkIndex() < lastBlock().checkIndex()){
        return false;
    } else if (newBlock.checkHash() != lastBlock().calculateHash()){
        return false;
    } else if (!(verifyProof(newBlock.getProofNum(), lastBlock().getProofNum()))){
        return false;
    } else if (newBlock.checkTimeStamp() <= lastBlock().checkTimeStamp()){
        return false;
    } else {
        return true;
    }
}

bool BlockChain::newData(const std::string& Sender, const std::string& Receiver, const std::string& Amount){
    currentData.push_back(Sender);
    currentData.push_back(Receiver);
    currentData.push_back(Amount);
    return true;
}

bool BlockChain::verifyProof(const int& lastProof, const int& proofNum){
    std::string guess = std::to_string(lastProof) + std::to_string(proofNum);
    std::string guessHash = sha256(guess);
    std::cout << "# Trying: " << guess << std::endl;
    if(guessHash.substr(0, 4) == "0000"){ // You can change the difficulty by adding or removing 0's (and updating substr). More 0's means higher difficulty.
        std::cout << "# FOUND: " << guessHash << std::endl;
        return true;
    }
    return false;
}

int BlockChain::proofOfWork(const int& lastProof){
    int proofNum = 0;
    while(verifyProof(proofNum, lastProof) == false){
        proofNum++;
    }
    return proofNum;
}

Block BlockChain::lastBlock(){
    return chain.back(); // This returns a reference of the last Block Object
}

void BlockChain::viewLastBlock(){
    std::cout << lastBlock(); // Sole purpose is to check to see if the genesis block was created correctly.
}

void BlockChain::viewChain(){
    for(auto block : chain){
        std::cout << block << std::endl;
    }
}