import java.net.*;
import java.io.*;
import java.util.*;

public class clientTCP{
	private static Socket so;
	
	private static String commande(String com){
		Scanner sc = new Scanner(System.in);
		String res = "";
		if(com.equals("DES")){
			String id;
			System.out.print("ID de l'article souhaité : ");
			id = sc.nextLine();
			return "DES ID "+id;
		}
		
		else if(com.equals("DEL")){
			String id;
			System.out.print("ID de l'article à supprimer : ");
			id = sc.nextLine();
			return "DEL ID "+id;
		}
	
		else if(com.equals("NEW")){
			String titre, port, msg;
			
			System.out.print("Titre : ");
			titre = sc.nextLine();
			titre = mod_space(titre);
			
			System.out.print("Port d'écoute pour l'annonce : ");
			port = sc.nextLine();
			
			System.out.print("Message à propos de l'annonce : ");
			msg = sc.nextLine();
			msg = mod_space(msg);
			
			return "NEW TITLE "+titre+" PORT "+port+" MESSAGE "+msg;
		}
	
		else if(com.equals("CON")){
			String id, ip = so.getInetAddress().toString();
			System.out.print("ID de l'article qui vous intéresse : ");
			id = sc.nextLine();
			return "CON ID "+id/*+" IP "+ip*/;
		}
		
		else{ return com; }
	}
	
	
	
	private static String mod_space(String m){
		String res = "";
		String[] tab = m.split(" ");
		for(String s : tab){ res += "\\ "+s;}
		return res.substring(2);
	}
	


	public static void main(String[] args){
		try{
			Scanner sc = new Scanner(System.in);
			Socket socket;
			if(args.length >2){return;}
			else if(args.length ==1){ socket=new Socket(args[0],7777); }
			else if(args.length == 2){ socket=new Socket(args[0],Integer.parseInt(args[1])); }
			else{
				InetAddress myIA=InetAddress.getLocalHost();
				socket=new Socket(myIA,7777);
			}
			so = socket;
			clientTCPReception cR = new clientTCPReception(socket);
			Thread t1 = new Thread(cR);
			t1.start();
			PrintWriter pw=new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
			pw.println("GET");
			pw.flush();
			while(true){
				String sent = sc.nextLine();
				sent = commande(sent);
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
