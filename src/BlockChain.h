#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <ctime>

class BlockChain{
    private:
    std::vector<Block> chain; // Keeps all blocks. Maybe a vector isn't the best for this?
    std::vector<std::string> currentData; // Keeps all completed transactions in the block.


    public:
        BlockChain();
        
        //Constructs Initial Block
        void constructGenesis();

        //Constructs and adds new block to chain.
        Block constructBlock(const int& proofNum, const std::string& prevHash);

        //Checks whether or not the Blockchain is valid
        bool checkValidity(Block& newBlock);

        //Adds a new transaction to the data of the transaction
        bool newData(const std::string& Sender, const std::string& Receiver, const std::string& Amount);

        // Protects blockchain from attack
        static bool constructProofOfWork();

        //Returns last block in the chain
        Block lastBlock();

        void viewChain();
};

#endif