I've always been intrigued by cryptocurrencies. I remember when I was 13 and stumbled across Bitcoin from a YouTube video,
and I instantly wanted to get my hands on some. I downloaded the Bitcoin core wallet and created an address and looked online
on how I could mine some for myself. But alas, my 13 year old brain could not comprehend the technical knowledge required to
join a mining pool on my mother's HP Laptop running Windows Vista.

"That's fine", I thought, "I'll just purchase some". Those dreams were quickly shut down as the price of one Bitcoin back then
was ~$250. This was a price an unemployed 13 year old who spent his time playing *Halo Reach* with his friends could not
afford.

Anyway, fast forward to 2021. Over the years, I managed to get my hands on various cryptos: Bitcoin Cash, Ethereum, Dogecoin.
I completely forgot about holding them, until one day I hear that the price of Dogecoin, a cryptocurrency created as a joke,
had risen to 31 cents. I quickly checked my wallet and lo' and behold, the 81 Dogecoin I was holding was worth $31.00 USD (at the time
of writing this, those 81 DOGE are now worth $50.82 USD).

With my interest in cryptocurrency suddenly renewed, I decided: "Hey, why not see if I could create my own blockchain? It'll be good
coding practice and I get a little crypto for my friends and I to fool around with".

#### <span class="span-underline">Selecting a Language and Learning Fundamentals</span>

I knew right from the onset I wanted to use C++ for this personal project, mostly because one of my friends doubted my ability in the language. The only issue was: I didn't have a single clue on how to start.

The first thing I wanted to understand is exactly HOW a blockchain works. I stumbled upon this very nice video which explains the basic fundamentals by YouTuber *3Blue1Brown*:

<div class="center-text">
<iframe width="560" height="315" src="https://www.youtube.com/embed/bBC-nXj3Ng4" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
</div>

In the video, 3Blue1Brown goes into great detail about **HOW** the public ledger works with digital signatures. Not only that, he also goes into how Proof of Work functions with the SHA256 cryptographic hash functions. Not only that, he also describes how "mining" works. I'm not going to go directly into the fundamentals on how these things work in this specific section, but I will once we start looking at - you guessed it - *the code*!

#### <span class="span-underline">To Fork, To Tokenize, or Build it Yourself</span>

Many of the mainstream cryptocurrencies today were built off of Forks of another coin. Litecoin was a fork of Bitcoin, Dogecoin was a fork of Litecoin, etc. I didn't want to just make a fork of a coin, as then all I'd have to do is change a few variables and be done with it.

I also didn't want to make a Token, which is a coin that runs on top of an already existing blockchain. That would also defeat the purpose of this whole thing, which was to "build my own blockchain".

So of course, I googled "How to build your own blockchain", and one of the first links my eyes saw was an article by Free Code Camp's *Alfrick Opidi*.

![Pic of Article](/static/img/fcc.png)
*[Click here to go to the article.](https://www.freecodecamp.org/news/create-cryptocurrency-using-python/)*

In the article, Opidi used Python - I want to use C++. But then I had a great idea: "Why don't I just use the article as a guide to write the C++ fundamentals?"

And so, that's kind of what I did. It was a great learning experience too, and I got to learn more about specific Python modules and had to get creative with reimplementing them in C++. It was also kind of frustrating, and it made me appreciate type declarations since guessing what a random variable is just by name can be difficult.

With a feasible guide, I decided it was finally time to get started on writing the code.

#### <span class="span-underline">Building Blocks (Code Ahead!)</span>

The first thing I did was look over the article and figure out what I should pieces of code I should delegate to other classes. Opidi had made all of the code within a single `py` file. While I could do this in C++, I also wanted to practice good coding styles.

The first thing I did was create two header files: One for the Block object, and the other for the Blockchain. I decided to work on the Block object first, since well... you can't really have a Blockchain without Blocks.

Blocks are actually quite simple objects. At their core, they store 5 separate data types:

- An Index Number of type `int`, which tells users where the block is located within the Blockchain.
- A Proof Number of type `int`, a number which can be used to verify the block in the chain.
- The hash of the previous block, of type `string`.
- Some form of data. Such as transactions or smart contracts. It needs to be able to grow, so `std::array` is out of the question. This can be stored in a `std::vector`.
- A timestamp of when the block was created, which can be represented as `std::string`.

Of course, these data types cannot be changed once the block is created, or else the entire blockchain could be compromised. So what I did when I created the `Block.h` file was store all of that data within private variables:

```cpp
#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
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
};
#endif
```

Of course, while we're in `Block.h` we might as well set up our function prototypes. We'll also need a cryptographic hashing function. I chose to go with SHA256, which I obtained as a header file as well. I didn't feel the need to download a whole cryptographic library for just one small project. Below is the completed `Block.h` file with all of our function protoypes set up. I didn't include the `SHA256.h` as it's quite large. If you're interested in checking it out, feel free to check this project's source code.

```cpp
#ifndef BLOCK_H
#define BLOCK_H

#include "SHA256.h"

#include <iostream>
#include <time.h>
#include <string>
#include <vector>

class Block{
    private:
        int blockIndex;
        int blockProofNum;
        std::string blockPrevHash;
        std::vector blockData;
        std::string blockTimeStamp;

    public:
        Block(const int& index, const int& proofNum, const std::string& prevHash, const std::vector<std::string>& data);

        ~Block();

        std::string calculateHash();

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
```

With our function prototypes set up, we can start properly defining `Block.cpp`. What better place to start than defining our constructor?

The role of the constructor is build the block data, so all there really is to do is just assign the private variables to something:

```cpp
#include "Block.h"

Block::Block(const int& index, const int& proofNum, const std::string& prevHash, const std::vector<std::string>& data){
    blockIndex = index;
    blockProofNum = proofNum;
    blockPrevHash = prevHash;
    blockData = data;
    blockTimeStamp = currentDateTime();
}
```

Everything seems good except for `blockTimeStamp`, which is expecting a return from `currentDateTime()`. Since I wanted our timestamp to be human readable, we can define `currentDateTime()` as the following (and yes, I did get this code off of cppreference):

```cpp
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
```

Eventually, we'll also want to be able to print out the block with std::cout for viewing purposes. So with a little operator overloading...

```cpp
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
```

Badda-bing badda boom! When we eventually use `std::cout` on our Genesis block, it'll come out nice and formatted like this:

```cpp
//Letting x be a placeholder for an int or string
{
Block Index: 0
Block Proof: 0
Previous Hash: 0
Block Data:
Block Time Stamp: XX/XX/XXXX
}
```

Utilizing `SHA256.h`, we can also very easily get the hash of all of this block's data. For now I just have all of the information concatenate into a string, and then hash that resulting string.

```cpp
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
```

And with that, we now have a functioning Block object. It's able to store important information about itself, calculate it's hash, and output itself in a user-readable format. With the exception of defining a few helper functions (which are used to just `return` private variables), we are ready to begin building the blockchain.

*I'll be utilizing those helper functions later on within the blockchain. If you want to see how they are defined, you can check out `Block.cpp` on my github:*

<div class="container center-text spacer-25px">
    <a href="https://github.com/dbentler/fccCoin_in_CPP/blob/main/src/Block.cpp">
        <button type="button" id="linkedin" onclick="" class="btn btn-dark btn-lg">Block.cpp Source Code</button>
    </a>
</div>

#### <span class="span-underline">Chaining Blocks Together</span>

Now that we have our `Block.cpp` and `Block.h` done, we can finally start work on building the blockchain.

Here we want every new Block's previous hash to point to block that came before it. We also out block index to represent it's place within our chain:

<img src="http://spheregen.com/wp-content/uploads/2019/04/blockchain.png" alt="Blockchain" class="center">
*A diagram of a Blockchain.*

We'll also need our blockchain to be secure, so we'll need it to do the following:

- Construct the first (genesis) block.
- Construct new blocks for the chain.
- Check the validity of new blocks.
- Hold transactions that will then be added to the new block upon creation.
- Utilize proof of work as a way for users to verify and mine new blocks.

With these factors in mind, we can set up our `Blockchain.h` file like this:

```cpp
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
        void constructGenesis();

        //Constructs and adds new block to chain.
        Block constructBlock(const int& proofNum, const std::string& prevHash);

        //Checks whether or not the Blockchain is valid
        bool checkValidity(Block& newBlock);

        //Adds a new transaction to the data of the transaction
        bool newData(const std::string& Sender, const std::string& Receiver, const std::string& Amount);

        // Protects blockchain from attack
        int proofOfWork(const int& lastProof);

        bool verifyProof(const int& lastProof, const int& proofNum);


        //Returns last block in the chain
        Block lastBlock();

        void viewLastBlock();

        //Prints out entire chain
        void viewChain();
};

#endif
```
*Non-Coders be like: I like your funny words magic man!*

Fantastic! I put `std::vector<Block>` chain and `std::vector<string>` currentData as private variables because I only want the Blockchain class to interact with them.

Diving into `Blockchain.cpp` now, we can utilize our constructor to construct the genesis block. This is quite easy to do - all that we need is for the constructor to call `constructGenesis()`, which can be defined the following way:

```cpp
#include "BlockChain.h"

BlockChain::BlockChain(){
    constructGenesis();
}

void BlockChain::constructGenesis(){
    constructBlock(0, "0");
}
```
Here we're creating the Genesis block, with an index and hash of `0`.

Of course, `constructGenesis()` is calling our BlockChain's `constructBlock()`. Defining `constructBlock(`) is pretty simple of course: We want to construct a new `Block` object, give that `Block` some information, verify if it's a valid block, and then add that block to the chain. If the block does get added to the chain, we also want to clear any data the Blockchain is holding after we pass it into the block.

Here's how we would implement that:

```cpp
Block BlockChain::constructBlock(const int& proofNum, const std::string& prevHash){

    Block block(chain.size(), proofNum, prevHash, currentData);

    currentData.clear(); // Clears transaction data for new blocks.

    if (block.checkIndex() == 0){ // This isn't secure. When I revist this I will work out a fix and update this section accordingly.
        chain.push_back(block);
        return block;
    }
    if (block.checkIndex() != 0){
        if (checkValidity(block)){
            chain.push_back(block);
            return block;
        } else {
            std::cout << "Block Rejected: invalid block!" << std::endl;
            return block;
        }
    }
}

bool BlockChain::checkValidity(Block& newBlock){
    if (newBlock.checkIndex() < lastBlock().checkIndex()){
        return false;
    } else if (newBlock.checkHash() != lastBlock().calculateHash()){
        return false;
    } else if (!(verifyProof(newBlock.getProofNum(), lastBlock().getProofNum()))){
        return false;
    } else {
        return true;
    }
}
```

Now I know what you may be asking: *"Hey Darren, what's that `verifyProof()`" function doing in `checkValidity()`"*? That's part of our Proof of Work that we haven't implemented yet!

Say, what is Proof of Work anyway? How do we implement it?

#### <span class="span-underline">Proof of Work</span>

At it's simplest, Proof of Work is when a "certain amount of computational effort has been expended for some purpose". This computational effort is the "Mining" that people do in order to verify a block.

Think of it as a very hard algebra problem, where `x + y = z`:

- `x` is unknown.
- `y` is known (the previous proof number)
- `z` is also unknown, but we know is must start with a certain number or amount of characters.

"Miners" basically try to guess the value of `x`, hash it with the value of `y`, and hope that they somehow get the answer to `z` before anyone else does. If they do, they can add a unique transaction to the Blockchain data that rewards them with some cryptocurrency.

Those who don't guess the correct values in time won't be rewarded with any cryptocurrency, but they are able to verify the correct guesser's work by checking if those `x` and `y` values truly equal `z`.

The "difficulty" of mining can be changed by changing what z must start with. For example, in the code below I want my z values to begin with four leading zeros: `0000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx`.

```cpp
bool BlockChain::verifyProof(const int& lastProof, const int& proofNum){
    std::string guess = std::to_string(lastProof) + std::to_string(proofNum);
    std::string guessHash = sha256(guess);
    std::cout << "# Trying: " << guess << " | Proof: "<< proofNum << std::endl;
    if(guessHash.substr(0, 4) == "0000"){ // You can change the difficulty by adding or removing 0's (and updating substr). More 0's means higher difficulty.
        std::cout << "# FOUND: " << guessHash << std::endl;
        return true;
    }
    return false;
}
```

If `verifyProof()` returns true, the `proofNum` would then be added to the new Block in the Blockchain.

Verifiers than can get the new Block's proof number with the previous Block's proof. If they check out, then the block is added to the chain.

And of course, if someone wants to become a miner on the chain, the function for that would look like this:

```cpp
int BlockChain::proofOfWork(const int& lastProof){
    int proofNum = 0;
    while(verifyProof(proofNum, lastProof) == false){
        ++proofNum;
    }
    return proofNum;
}
```

#### <span class="span-underline">Wrapping Things Together</span>

All that's really left in `Blockchain.cpp` is to define our helper functions, and a way to view the blockchain.

```cpp
Block BlockChain::lastBlock(){
    return chain.back(); // This returns a reference of the last Block Object
}

void BlockChain::viewLastBlock(){
    std::cout << lastBlock(); // Sole purpose is to view the last block.
}

void BlockChain::viewChain(){
    for(auto block : chain){
        std::cout << block << std::endl;
    }
}
```

And we are done! `Blockchain.h` and `Blockchain.cpp` are finally complete.

Now we can finally build our `main.cpp` file to test everything out. I personally set it to mine 3 blocks and then display our Blockchain.

```cpp
#include "BlockChain.h"

int main(){
   BlockChain blockchain = BlockChain();
   std::cout << "***Mining 3 additional blocks***" << std::endl;
   for(int i = 0; i < 3; i++){
      Block lastBlock = blockchain.lastBlock();
      int lastProof = lastBlock.getProofNum();
      int proofNum = blockchain.proofOfWork(lastProof);

      blockchain.newData("Darren", "Not Darren", "1.0");
      std::string lastHash = lastBlock.calculateHash();
      Block newBlock = blockchain.constructBlock(proofNum, lastHash);
   }
   std::cout << "***Done mining 3 blocks***" << std::endl;
   blockchain.viewChain();
}
```

After that, we just simply link all of our header files and compile, and we can see our blockchain and proof of work in action.

![Mining](/static/img/crypto.png)

#### <span class="span-underline">Conclusion</span>

That wraps up my little cryptocurrency adventure. I hope you found reading about it fun and easy to follow.

I decided to name this coin "Silicoin", a pun on the word "Silicon", and eventually distribute it amongst my friends and use it as a medium of exchange for virtual goods.

For example: In Settler's of Catan, instead of trading 3 sheep for 1 brick, you could trade X amount of Silicoin instead. Or you can use it as a sort of "Poker Chip" amongst your friends.

To do that though, I'll need to learn TCP networking and revisit how I handle transaction data. Not only that, I'll have to create a function wallet, and learn public-secret key encryption so I can implement digital signatures. Maybe that'll be a future project of mine.

<div class="container center-text spacer-25px">
    <a href="/projects">
        <button type="button" id="back" onclick="" class="btn btn-dark btn-lg">Go Back to Projects</button>
    </a>
    <a href="https://github.com/dbentler/fccCoin_in_CPP">
        <button type="button" id="linkedin" onclick="" class="btn btn-dark btn-lg">Blockchain Source Code</button>
    </a>
</div>
