#ifndef BLOCK_H 
#define BLOCK_H

#include <iostream>
#include "SHA256.h"
#include <string>
#include <vector>

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

        void viewBlock(); // Deprecated method

        friend std::ostream& operator <<(std::ostream& os, const Block& block);

        int checkIndex();
        double checkTimeStamp();
        std::string checkHash();

        int getProofNum();
};

std::ostream& operator <<(std::ostream& os, const Block& block);

#endif