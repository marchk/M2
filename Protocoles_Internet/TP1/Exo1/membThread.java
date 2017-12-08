import java.net.*;
import java.io.*;

public class membThread implements Runnable{
	public void run(){
		while(true){
			for(Socket s : serveurTCP.membres ){
				try{
					PrintWriter pw=new PrintWriter(new OutputStreamWriter(s.getOutputStream()));
					pw.println(serveurTCP.membres.size());
					pw.flush();
				}catch(Exception e){
				}
			}
			try{
				Thread.sleep(10000);
			}catch(Exception e){}
		}
	}
}
