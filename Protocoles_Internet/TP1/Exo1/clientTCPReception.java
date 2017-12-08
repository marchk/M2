import java.net.*;
import java.io.*;
import java.util.*;

public class clientTCPReception implements Runnable{
	final private Socket socket;

	public clientTCPReception(Socket s){ this.socket = s;}
	
	public void run(){
		BufferedReader br = null;
		try{
			br=new BufferedReader(new InputStreamReader(socket.getInputStream()));
			while(true){
				String mess=br.readLine();
				System.out.println("\nMessage recu :"+mess);
			}
		}
		catch(Exception e){
			if(br!=null){
				try{br.close();}catch(Exception ex){}
			}
		}
	}
}
