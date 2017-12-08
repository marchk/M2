import java.net.*;
import java.io.*;
import java.util.*;

public class serveurTCP{

	//static int nbmembres = 0;
	static ArrayList<Socket> membres;
		

	public static void main(String[] args){
		try{
			ServerSocket server;
			membres = new ArrayList<Socket>();
			if(args.length >1){return;}
			else if(args.length==1){ server=new ServerSocket(Integer.parseInt(args[0]));}
			else{ server=new ServerSocket(1027); }
			Thread mT = new Thread(new membThread());
			mT.start();
			while(true){
				Socket socket=server.accept();
				servThread st = new servThread(socket);
				Thread t = new Thread(st);
				t.start();
			}
		}
		catch(Exception e){
			//mT.stop();
			System.out.println(e);
			e.printStackTrace();
		}
	}
}
