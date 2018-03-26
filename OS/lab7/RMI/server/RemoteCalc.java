import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;

public class RemoteCalc extends UnicastRemoteObject implements Calc {
RemoteCalc() throws RemoteException {
        super();
}
public int add(int x,int y){
        return x+y;
}
public int sub(int x,int y){
        return x-y;
}
public int mul(int x,int y){
        return x*y;
}
public static void main(String args[]){
        try{
                Calc stub=new RemoteCalc();
                Naming.rebind("rmi://localhost:3000/calc",stub);
        }catch(Exception e) {
                System.out.println(e);
        }
}

}
// rmiregistry 3000
// java RemoteCalc
