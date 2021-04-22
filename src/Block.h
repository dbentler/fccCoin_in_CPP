#ifndef BLOCK_H 
#define BLOCK_H

#include <iostream>
#include "SHA256.h"
#include <time.h>
#include <string>
#include <vector>

class Block{
    private:
        int blockIndex; 
        int blockProofNum;
        std::string blockPrevHash;
        std::vector<std::string> blockData;
        std::string blockTimeStamp;
        
    public:
        Block(const int& index, const int& proofNum, const std::string& prevHash, const std::vector<std::string>& data);

        ~Block();

        std::string calculateHash();

        void viewBlock(); // Deprecated method

        friend std::ostream& operator <<(std::ostream& os, const Block& block);

        //Time
        friend const std::string currentDateTime();

        //Helper functions to access private block variables.
        int checkIndex();
        std::string checkTimeStamp();
        std::string checkHash();
        int getProofNum();
};

std::ostream& operator <<(std::ostream& os, const Block& block);

const std::string currentDateTime();

#endif