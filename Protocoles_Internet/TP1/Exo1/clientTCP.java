import java.net.*;
import java.io.*;
import java.util.*;

public class clientTCP{
	public static void main(String[] args){
		try{
			Socket socket;
			if(args.length >2){return;}
			else if(args.length ==1){ socket=new Socket(args[0],1027); }
			else if(args.length == 2){ socket=new Socket(args[0],Integer.parseInt(args[1])); }
			else{
				InetAddress myIA=InetAddress.getLocalHost();
				socket=new Socket(myIA,1027);
			}
			clientTCPReception cR = new clientTCPReception(socket);
			Thread t1 = new Thread(cR);
			clientTCPEnvoi cE = new clientTCPEnvoi(socket,t1);
			Thread t2 = new Thread(cE);
			t1.start(); t2.start();
		}
		catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
		}
	}
}
