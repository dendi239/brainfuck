+>+>> set first three bytes 110
>> reserve place for number of tests

,>+++++[<-->-]< read symbol minus line feed 
[
  >++++++[<------>-]<-- make it digit
  <<
   copy test number to three places to the right
     [->>>+>>+<<<<<]>>>>>[-<<<<<+>>>>>]<<<<<
    >[->>>+>>+<<<<<]>>>>>[-<<<<<+>>>>>]<<<<<<
    >>>[-<<<
      +>+<[>-<<]<[>]>  add one with overflow
      +>+<[>-<<]<[>]>  add two with overflow
      +>+<[>-<<]<[>]>  add three with overflow
      +>+<[>-<<]<[>]>  add four with overflow
      +>+<[>-<<]<[>]>  add five with overflow
      +>+<[>-<<]<[>]>  add six with overflow
      +>+<[>-<<]<[>]>  add seven with overflow
      +>+<[>-<<]<[>]>  add eight with overflow
      +>+<[>-<<]<[>]>  add nine with overflow
         >>>]<<<
    >>>>[-<<<+++++++++>>>]<<<<  add nine for top byte
  >>
  [-<<
    +>+<[>-<<]<[>]>  add one with overflow
    >>]
  ,>+++++[<-->-]< read symbol minus line feed
]

check if number of tests is not zero 
<<[>>+<<<]<[>]>>> 
< [> +<<<]<<[>]>>>

[
  [-]
  <<
   >-<[>+<<]<[>]>-  remove one with overflow
  >>
  
  > reserve one bit for answer
  ,>+++++[<-->-]< read symbol minus line feed 
  [
    
    >+++++++++[-<-------->]<---- V becomes zero
    >>+<< make 01 after symbol
    
      <+>[<->>]>[<]< IF zero then flag is nonzero
      ---- if Z then now zero
      <+>[<->>]>[<]< IF zero then flag is nonzero

    [-]>>-<< clear
    ,>+++++[<-->-]< read symbol minus line feed 
  ]
  <
  
  >+<
  [[-]>[-]<
    PRINT YES
    >+++++++++[-<++++++++++>]<-.
    >++++[-<----->]<.
    >++[-<+++++++>]<.
    [-]>++[-<+++++>]<.
    [-]
  ]
  >[[-]>[-]<
    PRINT NO
    >++++++++[-<++++++++++>]<--.
    +.
    [-]>++[-<+++++>]<.
    [-]
  ]<
    
  [-]
  check if number of tests is not zero
  <<[>>+<<<]<[>]>>> 
  < [> +<<<]<<[>]>>>
]