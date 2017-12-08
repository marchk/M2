import java.net.*;
import java.io.*;
import java.util.*;

public class clientTCPEnvoi implements Runnable{
	final private Socket socket;

	public clientTCPEnvoi(Socket s, Thread t){ 
		this.socket = s;
	}
	
	public void run(){
		try{
			Scanner sc = new Scanner(System.in);
			PrintWriter pw=new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
			while(true){
				String sent = sc.nextLine();
				pw.println(sent);
				pw.flush();
				if(sent.equals("BYE") || sent==null){break;}
			}
			pw.close();
			socket.close();
		}
		catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
		}
	}
}
