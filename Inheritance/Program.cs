using System;

IO_.Serial aPort;
aPort = new IO_.finalio();

object obj;
obj = aPort;


//aPort = new IO_.Serial();
Console.WriteLine("Hello World!");




namespace IO_ {

    public delegate void OnReceive(String S);
    public interface Isample {
        void send(String S);
        void receive(OnReceive S);
        void initialize();
    }


    abstract class Serial : Isample
    {
        public void send(String S) {
            
        }
        public void receive(OnReceive S) { }
        public void initialize() { }
        public abstract void test(String S);

    }

       
    class finalio : Serial {
        public override void test(String S) {            
        } 
    }

    class SPA {
        public SPA(Isample S) {            
        }
    }


}