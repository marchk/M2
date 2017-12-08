import java.net.*;
import java.io.*;

public class servThread implements Runnable{
	private Socket socket;
	
	
	public servThread(Socket sock){
		this.socket = sock;
		ajoute();
	}
	
	synchronized void ajoute(){
		serveurTCP.membres.add(this.socket);
	}
	
	synchronized void retire(){
		serveurTCP.membres.remove(this.socket);
	}
	
	
	public void run(){
		try{
			BufferedReader br=new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter pw=new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
			pw.print("HI ! members connected : "+serveurTCP.membres.size()+"\n");
			pw.flush();
			while(true){
				String mess=br.readLine();
				InetAddress sockAdr = socket.getInetAddress();
				System.out.println("Message recu : \""+mess+"\"\n(Envoyé par "+sockAdr+")\n");
				String rep = "reçu";
				if(mess.equals("members")){ rep = ""+ serveurTCP.membres.size(); }
				pw.println(rep);
				pw.flush();
				if(mess.equals("quit") || mess==null){
					break;
				}
			}
			br.close();
			pw.close();
			socket.close();
			retire();
		}catch(Exception e){
			retire();
		}
	}
}
