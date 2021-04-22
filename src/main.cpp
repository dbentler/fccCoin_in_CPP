
#include "BlockChain.h"

int main(){
   BlockChain blockchain = BlockChain();
   std::cout << "***Mining fccCoin about to start!" << std::endl;
   Block lastBlock = blockchain.lastBlock();
   int lastProof = lastBlock.getProofNum();
   int proofNum = blockchain.proofOfWork(lastProof);

   blockchain.newData("Darren", "Not Darren", "1.0");

   std::string lastHash = lastBlock.calculateHash();
   Block newBlock = blockchain.constructBlock(proofNum, lastHash);
   
   std::cout << "***Mining fccCoin has been successful!***" << std::endl;
   blockchain.viewChain();
}