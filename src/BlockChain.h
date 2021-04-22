#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"


class BlockChain{
    private:
    std::vector<Block> chain; // Keeps all blocks. Maybe a vector isn't the best for this?
    std::vector<std::string> currentData; // Keeps all completed transactions in the block.


    public:
        BlockChain();
        
        //Constructs Initial Block
        Block constructGenesis();

        //Constructs and adds new block to chain.
        Block constructBlock(const int& proofNum, const std::string& prevHash);

        //Checks whether or not the Blockchain is valid
        bool checkValidity(Block& newBlock);

        //Adds a new transaction to the data of the transaction
        void newData();

        // Protects blockchain from attack
        static bool constructProofOfWork();

        //Returns last block in the chain
        Block lastBlock();
};

#endif