#ifndef BLOCK_H 
#define BLOCK_H

#include <string>
#include <vector>
#include <set>

class Block{
    private:
        int blockIndex; 
        int blockProofNum;
        std::string blockPrevHash;
        std::vector<std::string> blockData;
        double blockTimeStamp;
        
    public:
        Block(const int& index, const int& proofNum, const std::string& prevHash, const std::vector<std::string>& data, const double& timeStamp);

        ~Block();

        std::string calculateHash();

        void viewBlock();
};

#endif