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
				if((mess!=null)&&(!mess.equals(""))){
					if(mess.startsWith("CON PORT")){
						try{
							String[] ms = mess.split(" ");
							String port = ms[2], ip = ms[ms.length-1];
							Popup pu = new Popup(ip,port,socket);
						}catch(Exception e){}
					}
					
					else if(mess.startsWith("OK IP")){
						String[] ms = mess.split(" ");
						String ip = ""; int port=0;
						for(int i=0; i<ms.length; i++){
							if(ms[i].startsWith("IP")){ip = ms[i+1];}
							else if(ms[i].startsWith("PORT")){port = Integer.parseInt(ms[i+1]);}
						}
						if(mess.contains("HOST")){
							Hote h = new Hote(port);
							Thread th = new Thread(h);
							th.start();
						}
						else{
							Client c = new Client(port,ip);
							Thread tc = new Thread(c);
							tc.start();
						}
					}
					System.out.println("\""+mess+"\"");
				}
			}
		}
		catch(Exception e){
			if(br!=null){
				try{br.close();}catch(Exception ex){}
			}
		}
	}
}
