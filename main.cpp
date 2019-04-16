/* 
 * File:   main.cpp
 * Author: Aesys_2018
 *
 * Created on 16 aprile 2019, 16.53
 */

#include <iostream>
#include <string>

template <typename OutputPolicy,  class  LanguagePolicy>
class HelloWorld : private OutputPolicy, private LanguagePolicy
{
    using OutputPolicy::print;
    using LanguagePolicy::message;
 
public:
    // Behaviour method
    void run() const
    {
        // Two policy methods
        print(message());
    }
};
 
class OutputPolicyWriteToCout
{
protected:
    template<typename MessageType>
    void print(MessageType&& message) const
    {
        std::cout << message << std::endl;
    }
};

template<typename V>
class T {
protected:
   virtual std::string  loadContent()=0;
 
public:   
    virtual V message() const=0; 
};


template<typename V>
class F {
 
public:   
    virtual V operator()(V msg) const=0; 
    
    
};

class Testo : public F <std::string>
{
public:
    std::string operator()(std::string content) const{
        return content;
    }
     virtual std::string message() const {
         return ("ciao bello");
     }
};

class Text : public T<std::string>
{
    
   std::string  content {"Hello World"};
   
protected:
    std::string  loadContent() {};
public:
    Text(){};
         
    Text(std::string  ss) : content(ss) {}; 
    
        

    virtual std::string message() const {
        return content ;
    };

};

class TextWelcome : public T<std::string>
{
    
   std::string  content {"Welcome Guy"};
protected:
   std::string  loadContent() {content= "Welcome Joe";};
public:
    TextWelcome(){};
    TextWelcome(std::string  ss) : content(ss) {}; 
    
    virtual std::string message() const {
         
        return content ;
    };

};


template <class V,class F>
class LanguagePolicyItalian
{     
   F msg; 
public :
            
    V message( ) const
    {
        return msg.message();
    }
};

template <class V,class F>
class LanguagePolicyItalianFunct
{     
   F msg;
   std::string mymsg;
public :
            
    LanguagePolicyItalianFunct():mymsg(""){};
    LanguagePolicyItalianFunct(std::string _mymsg) : mymsg(_mymsg){};;
    V message( ) const
    {
        return msg("ciao Funct");
    }
};



template <class V,class T>
class LanguagePolicyEnglish
{     
   T msg; 
public :
            
    V message( ) const
    {
        return msg.message();
    }
};
 
class LanguagePolicyGerman
{
protected:
    std::string message() const
    {
        return "Hallo Welt!";
    }
};
 
int main()
{
    /* Example 1, simple */
    typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyGerman> HelloWorldGerman;
 
    HelloWorldGerman hello_world2;
    hello_world2.run(); // prints "Hallo Welt!"
    
    
    /* Example 2, policy using two template */
    typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyEnglish<std::string,Text>> HelloWorldEnglish;
    typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyEnglish<std::string,TextWelcome>> WelcomeGuyEnglish;
  
    HelloWorldEnglish hello_world;
    hello_world.run(); // prints "Hello, World!"
    WelcomeGuyEnglish  wg;
    wg.run();
    
    
    /* Example 3, policy using functor*/
  
    
    typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyItalian<std::string,Testo>> CiaoBelloItalian;
    typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyItalianFunct<std::string,Testo>> CiaoBelloItalianFunct;
   
    CiaoBelloItalian cbi;
    
    cbi.run ();
    
    CiaoBelloItalianFunct cbif ;
    
    cbif.run();
    
}