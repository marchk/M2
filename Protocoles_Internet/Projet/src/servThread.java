import java.net.*;
import java.io.*;
import java.util.*;
import java.security.MessageDigest;

public class servThread implements Runnable{
	private Socket socket;
	
	
	public servThread(Socket sock){  this.socket = sock;  }


	public Socket getSocket(){  return this.socket;  }

	
	private String help(){  return serveurTCP.man;  }
		
	
	private synchronized String show_announces(){
	//----Affiche les annonces----
		String res = "";
		for(Socket mem : serveurTCP.members){
			ArrayList<String> list = serveurTCP.announces.get(mem.getInetAddress().toString());
			for(String ann : list){
				String[] spl = ann.split("%%");
				String adre = spl[0], id = spl[1], port = spl[2], titre = spl[3], data = spl[4];
				res += "ADD ID "+id+" TITLE "+titre+"\n";
			}
		}
		if(res.equals("")){res = "Pas d'annonces !";}
		return res;
	}
	
	
	private synchronized String des_announce(String m){
	//----Affiche une annonce complète----
		String res = "DES ";
		try{
			String idm = null;
			String[] ab = m.split(" ");
			for(int i=0; i< ab.length; i++){ if(ab[i].startsWith("ID")){ idm = ab[i+1]; break; } }
			for(Socket mem : serveurTCP.members){
				ArrayList<String> list = serveurTCP.announces.get(mem.getInetAddress().toString());
				for(String ann : list){
					String[] spl = ann.split("%%");
					String adre = spl[0], id = spl[1], port = spl[2], titre = spl[3], data = spl[4];
					if(id.equals(idm)){			
						res += "ID "+id+" PORT "+port+" TITLE "+titre+" MESSAGE "+data;
						return res;
					}
				}
			}
			return "NON";
		}catch(Exception e){ return "NON";}
	}
	
	
	private synchronized void send_members(String m){
	//----Envoie la chaîne de caractère m à tous les membres connectés----
		for(Socket s : serveurTCP.members ){
			try{
				PrintWriter pw=new PrintWriter(new OutputStreamWriter(s.getOutputStream()));
				pw.println(m);
				pw.flush();
			}catch(Exception e){del_announces(s.getInetAddress().toString()); continue;}
		}
	}
	
	
	private synchronized String add_announce(String m){
	//----Ajoute une annonce dans la banque de données et préviens les membres connectés----
		try{
			String[] spl = m.split(" ");
			String titre = null, port = null, data = null, id = null,adre = this.socket.getInetAddress().toString();
			int j;
			for(int i=0; i<spl.length; i++){
				j=i+1;
				if(spl[i].startsWith("TITLE")){
					titre = spl[i+1];
					while(j<=spl.length-2){
						if(spl[j].charAt(spl[j].length()-1) == '\\'){
							titre = titre.substring(0, titre.length()-1) +" "+spl[j+1];
							j++;
						}
						else{i=j;break;}
					}
				}
				
				
				else if(spl[i].startsWith("PORT")){
					port = spl[i+1];
				}
				
				
				else if(spl[i].startsWith("MESSAGE")){
					data = spl[i+1];
					while(j<=spl.length-2){
						if(spl[j].charAt(spl[j].length()-1) == '\\'){
							data = data.substring(0, data.length()-1) +" "+spl[j+1];
							j++;
						}
						else{i=j;break;}
					}
				}
				
			}
			if(titre==null || port==null){return "NON";}

			MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
			messageDigest.update(m.getBytes());
			id = ""+(new String(messageDigest.digest())).hashCode();
			String ann = adre+"%%"+id+"%%"+port+"%%"+titre+"%%"+data;
			serveurTCP.ajoute(this.socket.getInetAddress().toString(), ann);
			String ret = "ADD ID"+id+" TITLE"+titre;
			send_members(ret);
			return "OK";
		}catch(Exception e){
			return "";
		}
	}
	
	
	
	
	private synchronized void del_announces(String ad){
	//----Supprime toutes les annonces d'un membre et prévient les membres connectés----
		try{
			ArrayList<String> list = serveurTCP.announces.get(this.socket.getInetAddress().toString());
			for(String ann : list){
				String[] spl = ann.split("%%");
				String adre = spl[0], id = spl[1], port = spl[2], titre = spl[3], data = spl[4];
				if(adre.equals(ad)){
					send_members("DEL ID"+id);
					list.remove(ann);
				}
			}
		}catch(Exception e){}
	}
	
	
	
	private synchronized String del_ann(String m){
	//----Supprime une annonce et prévient les membres connectés----
		try{
			String id = null;
			String[] ab = m.split(" ");
			for(String s : ab){ if(s.startsWith("ID")){ id = s.substring(2); break; } }
			ArrayList<String> list = serveurTCP.announces.get(this.socket.getInetAddress().toString());
			for(String ann : list){
				String[] spl = ann.split("%%");
				String adre = spl[0], id2 = spl[1], port = spl[2], titre = spl[3], data = spl[4];
				if(id.equals(id2)){
					send_members("DEL ID"+id);
					list.remove(ann);
					return "OK";
				}
			}
			return "NON";
		}catch(Exception e){return "NON";}
	}
	
	
	private String ipForId(String id){
		for(Socket r1 : serveurTCP.members){
			String r = r1.getInetAddress().toString();
			ArrayList<String> ann = serveurTCP.announces.get(r);
			for(String a : ann){
				String[] s = a.split("%%");
				String adre = s[0], ida = s[1];
				if(id.equals(ida)){return adre;}
			}
		}
		return null;
	}
	
	private String portForId(String id){
		for(Socket r1 : serveurTCP.members){
			String r = r1.getInetAddress().toString();
			ArrayList<String> ann = serveurTCP.announces.get(r);
			for(String a : ann){
				String[] s = a.split("%%");
				String port = s[2], ida = s[1];
				if(id.equals(ida)){return port;}
			}
		}
		return null;
	}
	
	
	private String connect_to(String m){
	//----Tente de mettre deux clients en relation----
		try{
			String[] opt = m.split(" ");
			if(opt[1].startsWith("ID")){
				String id = opt[2];
				
				String ip = ipForId(id);
				String port = portForId(id);
				
				Socket s = null;
				for(Socket z : serveurTCP.members){
					if(z.getInetAddress().toString().equals(ip)){s=z;}
				}
				
				PrintWriter pw2=new PrintWriter(new OutputStreamWriter(s.getOutputStream()));
				BufferedReader br2=new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
				
				pw2.println("CON PORT "+port);
				pw2.flush();
				while(true){
					String mess=br2.readLine();
					if(mess.equals("OK CON")){
						pw2.close();
						br2.close();
						return "OUI IP "+s.getInetAddress().toString().substring(1)+" PORT "+port;
					}
					else{break;}
				}
				pw2.close();
				br2.close();
				return "NON";
			}
			else{ return "NON"; }
		}catch(Exception e){ e.printStackTrace();return "NON";}
	}
	

	private String read_exec(String m){
	//----Traîtement d'une commande----
		try{
			String[] opt = m.split(" ");
			if(m.equals("GET")){
				return show_announces();
			}
			
			else if(opt[0].equals("DES")){
				return des_announce(m);
			}
			
			else if(opt[0].equals("DEL")){
				return del_ann(m);
			}
		
			else if(opt[0].equals("NEW")){
				return add_announce(m);
			}
		
			else if(opt[0].equals("CON")){
				return connect_to(m);
			}
		
			else if(opt[0].equals("HLP")){
				return help();
			}
		
			else{
				return "";
			}
		}catch(Exception e){
			return "NON";
		}
	}



	
	public void run(){
		try{
			BufferedReader br=new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter pw=new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
			InetAddress sockAdr = socket.getInetAddress();
			//pw.println("HI "+sockAdr+" !");
			//pw.flush();
			while(true){
				String mess=br.readLine();
				if(mess.equals("BYE") || mess==null){
					pw.flush();
					break;
				}
				String rep = read_exec(mess);
				pw.println(rep);
				pw.flush();
				System.out.println("\nMessage recu : \""+mess+"\"\n(Envoyé par "+sockAdr+")\n");
				
			}			
			del_announces(socket.getInetAddress().toString());
			serveurTCP.disconnect(this.socket);
			br.close();
			pw.close();
			socket.close();
		}catch(Exception e){
			del_announces(socket.getInetAddress().toString());
			serveurTCP.disconnect(this.socket);
		}
	}
}
