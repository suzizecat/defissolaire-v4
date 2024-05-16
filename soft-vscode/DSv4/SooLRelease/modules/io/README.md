# sool::io
IO Module repository

# Quicks setups
Once you have the sources configured in your project, it is easy to set a simple input/output flow handler

## Output flow setup
In order to set a simple output flow, you need to 
 1. setup your transmission peripheral (here USART2, through a custom `setup_usart2()` function);
 2. create a function to send a single byte with the prototype `void your_handler(char aCharToSend)`, here called `printc`;
 3. declare a characters buffer, usually you can go with rather small buffers such as 24 bytes;
 4. declare the output handler (here `sout`) providing the buffer address and its size;
 5. link the "sender" function to the handler through `set_on_send_handler`.
 
 Here you go ! You can now use `sout.print()` to send data however you wish over your port.
 
```cpp
void printc(char c)
{
	while(! sool::core::USART2->SR.TXE)
		asm("nop");

	sool::core::USART2->DR = c;
}

int main()
{
  setup_usart2();
  char tx_buffer[24];
  sool::io::IOBufferTX sout(tx_buffer, 24);
  sout.set_on_send_byte(printc);
  
  sout.print("Hello World !");
}
```

## Input flow setup
A basic input setup will require to "catch" any incomming byte comming from a communication port, adding it to the port handler which will check the incomming byte using a user defined function, a **validator**. Upon positive feedback from the validator, a user defined handler can be called.

You will need to :
 1. set up your transmission peripheral (here USART2, through a custom `setup_usart2()` function);
 2. declare an input buffer which might be rather large;
 3. declare your RX handler (here `sin`);
 4. set up the "catcher" function, here we will use the USART2 interrupt. This function must catch each character (byte) and use `put(char c)` to add it to the RX buffer;
 5. set up a "validator" (here `rx_validator`) which will return a non-zero value when user criteria are met (usually when a given character like '\n' or '\r' (new line) is given).
 6. set up a handler, called when the buffer is validated (here `on_valid_input()`).
 7. link the handler to the `IOBufferRX` object though `set_on_valid_input()`
 
 And here you go !
 Here, the STM will output the string you wrote upon hitting enter.
 
 Since all of the handling process is done while in interrupt, you should be careful to not put too much code in the handler. Rather, set a global variable with a proper value and use is in the rest of your software.
 
```cpp
char rx_buffer[100];
sool::io::IOBufferRX sin(rx_buffer,100);

extern "C" {
  void USART2_IRQHandler()
  {
    if(sool::core::USART2->SR.RXNE)
    {
      sin.put(sool::core::USART2->DR.DR);
    }
  }
}

int rx_validator(IOBufferRX& aRX,char aChar)
{
  if(aChar == '\r')
	  return 1;
  
  return 0;
}

void on_valid_input (IOBufferRX& rx_handler, int validatorOutput)
{
  char temp[100];
  rx_handler.transfer(temp);
  sout.print(temp);
}

int main()
{
  setup_usart2();
  sin.set_validator(rx_validator);
  sin.set_on_valid_input(on_valid_input);
  
  while(1);
}
 ```
