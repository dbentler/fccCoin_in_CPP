#include "Block.h"

Block::Block(const int& index, const int& proofNum, const std::string& prevHash, const std::vector<std::string>& data){
    blockIndex = index;
    blockProofNum = proofNum;
    blockPrevHash = prevHash;
    blockData = data;
    blockTimeStamp = currentDateTime();
}

Block::~Block(){};

std::string Block::calculateHash(){
    //TO DO, find a better way to calculate the hash of the block.
    std::string blockAsString;
    blockAsString = std::to_string(blockIndex) + std::to_string(blockProofNum) + blockPrevHash;
    std::string dataString;
    
    for (auto i : blockData){
        dataString += i;
    }

    blockAsString += (dataString + blockTimeStamp);

    return sha256(blockAsString);
}

void Block::viewBlock(){
   std::cout << "{" << std::endl;
   std::cout << "Block Index: " << blockIndex << std::endl;
   std::cout << "Block Proof: " << blockProofNum << std::endl;
   std::cout << "Previous Hash: " << blockPrevHash << std::endl;
   std::cout << "Block Data: ";
   for(auto i : blockData){
       if(i != blockData.back()){
            std::cout << i << ", ";
       } else {
           std::cout << i;
       }
   }
   std::cout << "\nBlock Time Stamp: " << blockTimeStamp << std::endl;
   std::cout << "}" << std::endl;
   std::cout << "This block was outputted with a deprecated method!" << std::endl;
}

int Block::checkIndex(){
    return blockIndex;
}

std::string Block::checkTimeStamp(){
    return blockTimeStamp;
}

std::string Block::checkHash(){
    return blockPrevHash;
}

int Block::getProofNum(){
    return blockProofNum;
}

std::ostream& operator <<(std::ostream& os, const Block& block){
    os << "{" << std::endl;
    os << "Block Index: " << block.blockIndex << std::endl;
    os << "Block Proof: " << block.blockProofNum << std::endl;
    os << "Previous Hash: " << block.blockPrevHash << std::endl;
    os << "Block Data: ";
    for(auto i : block.blockData){
       if(i != block.blockData.back()){
            os << i << ", ";
        } else {
            os << i;
        }
   }
   os << "\nBlock Time Stamp: " << block.blockTimeStamp << std::endl;
   os << "}" << std::endl;
   return os;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}