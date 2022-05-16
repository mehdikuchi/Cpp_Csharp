using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mehdi

{
    delegate void Notifier(string S);
    class Model {
        public event Notifier notifyViews;
        public enum Idfile { first,second};

        public struct database {
            int data;
            String name;
        }
        public void Change() {
            notifyViews("Model");
        }
        public void selfupdate(String S) {
            System.Console.WriteLine("This is from itself " + S);
        }
        public Model() {
            this.notifyViews += new Notifier(this.selfupdate);
        }
    }
    class View1 {
        public View1(ref Model M) { 
            M.notifyViews += new Notifier(this.Update1);
        }
        public void Update1(String sender) {
            System.Console.WriteLine(sender + " was changed");
        }
    }
    class View2 {
        public View2(ref Model M) {
            M.notifyViews += new Notifier(this.Update2);
        }
        public void Update2(String sender) {
            System.Console.WriteLine(sender + " was changed");
        }
    }
}
