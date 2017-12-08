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
					if(mess.startsWith("CON")){
						String[] ms = mess.split(" ");//"CON IDid IPip PORTport
						String ip = "";
						int port =0;
						for(String str : ms){
							if(str.startsWith("PORT")){ port = Integer.parseInt(str.substring(4)); }
							else if(str.startsWith("IP")){ ip = str.substring(3); }
						}
						try{
							Hote h = new Hote(port);
							Thread th = new Thread(h);
							th.start();
							PrintWriter pw2=new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
							pw2.println("OK IP"+ip);
							pw2.flush();
						}catch(Exception e){ 
							PrintWriter pw2=new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
							pw2.println("NON IP"+ip);
							pw2.flush();
						}
					}
					else if(mess.startsWith("ADD")){
						String[] ms = mess.split(" ");
						for(int i=0; i<ms.length; i++){
							String sm =ms[i];
							int j = i+1;
							while(j<ms.length && !ms[j].equals("ADD")){
							//ADD ID id TITRE titre
								sm += " "+ms[j];
								j++;
							}
							System.out.print(sm);
							i=j;
							System.out.print("\n");
						}
					}
					else if(mess.startsWith("OK IP")){
						String[] ms = mess.split(" ");
						String ip = ""; int port=0;
						for(int i=0; i<ms.length; i++){
							if(ms[i].startsWith("IP")){ip = ms[i].substring(3);}
							else if(ms[i].startsWith("PORT")){port = Integer.parseInt(ms[i].substring(4));}
						}
						Client c = new Client(port,ip);
						Thread tc = new Thread(c);
						tc.start();
					}
					
					else{
						String[] ms = mess.split("@");
						System.out.print("Reçu du serveur :\n\"");
						for(int i=0;i<ms.length; i++){
							System.out.println(ms[i]);
						}
						System.out.print("\"\n");
					}
				}
			}
		}
		catch(Exception e){
			//e.printStackTrace();
			if(br!=null){
				try{br.close();}catch(Exception ex){/*ex.printStackTrace();*/}
			}
		}
	}
}
