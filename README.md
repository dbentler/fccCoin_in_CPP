# fccCoin Blockchain, rewritten in C++
My interest in cryptocurrency has been renewed lately, in part by the price of Dogecoin suddenly exploding and making my 81 Dogecoin equivalent to $31.00 USD.

Anyway, this got me looking into Blockchain technology and curious about how to write a basic implementation of one, and I ended up stumbling upon Free Code Camp's ["How to Create Your Own Cryptocurrency Using Python"](https://www.freecodecamp.org/news/create-cryptocurrency-using-python/) by Alfrick Opidi.

And now while I am a huge Python fanatic, I also didn't want to just copy and paste the code in the article.
So I decided to rewrite the Python code in the article into C++.

## But why would you do such a thing?
As I stated before, I didn't want to just copy and paste the code from the article into VS Code and run it and be like "Heh, cool". I wanted to challenge myself and use the article as a sort of "pseudo-code" template and make it a personal challenge to translate it into C++.

This way, I'll get practice with breaking up my code into Header files, Object Oriented Programming, Git, and tooling around with my compiler (GCC). Most importantly, it's C++ practice.
## Python != C++. You won't be able to translate it 1:1...
That's part of the fun, and makes this challenge more than just transliteration.  I actually have to think outside of the box and really understand how something such as Python's `__repr__` works if I want to implement the same functionality in C++.
So not only am I learning more about C++, I guess I'm also learning more about Python as well.

## This code is unfinished.
I did say part of this project was also to practice Git. Can't really do that if I only upload the finished product. Come view my mistakes and how I later correct them down the line! 

## Update 22 April, 2021 - IT WORKS
Finally, after two days of nonstop coding, I've successfully recreated the output of the original article (I took liberties with the Block format of course):
![I was ecstatic when the correct hash was found.](https://i.imgur.com/2ZW3VtC.png)

Now I need to go back and investigate my implementation of CTime, as well as a better indication that the mining is taking place instead of just throwing an insane amount of hashes at the screen before coming to an abrupt stop.
