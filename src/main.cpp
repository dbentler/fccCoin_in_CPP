
#include "BlockChain.h"

int main(){
   BlockChain blockchain = BlockChain(); // BlockChain init
   blockchain.viewChainTest(); // Check for last block in chain.
   blockchain.newData("Darren", "Not Darren", "1.0"); // Test data
   //Test for Blockchain additions
   std::string lastHash = blockchain.lastBlock().calculateHash(); 
   Block block = blockchain.constructBlock(1, lastHash);
   blockchain.viewChainTest();
}