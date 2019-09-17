import java.util.ArrayList;

public class Library {
	
	ArrayList<Material> materials = new ArrayList<Material>();// ���� �ڷ���� �����ϴ� �迭
	ArrayList<Visitor> visitors = new ArrayList<Visitor>();// ������ �湮������ ����� �����ϴ� �迭
	ArrayList<Visitor> members = new ArrayList<Visitor>();// ȸ�� ��� �迭
	static ArrayList<Visitor> blcokmember = new ArrayList<Visitor>(); //�߰�������� ���ܸ�� ȸ�� ����� ����Ʈ�� ��Ƴ���.
	
	SearchGate gate = new SearchGate(); //�������� �����ϴ� ���Ȱ˻���
	
	public boolean enter(Visitor v){ //�湮�ڰ� �湮�� �ϸ�
		if(gate.enter(v)) //���Ȱ˻��뿡 ����� ����� ���尡��, ���� ȸ���� ���� �Ұ�
		{	
		System.out.println(v.name+" �����Ͽ����ϴ�.");
		visitors.add(v);//visitors ����Ʈ�� �ش� �湮�� ��ü �߰�
		if(v instanceof Member) {members.add(v);} //���� �湮�ڰ� ȸ���̶�� ȸ�� ��Ͽ� �߰�
		System.out.println("���� �湮�� ��: "+visitors.size());
		return true;
		}
		else
		return false; //����ȸ���̶�� ������ �Ƚ�Ų��.
	}
	
	public void exit(Visitor v){
		if(gate.search(v)){  // ������ �ܺη� ������ �޼ҵ� ���� �뿩���� �ʴ� �ڷᰡ�ִٸ� ������ ����
			System.out.println(v.name+" �����մϴ�");
			visitors.remove(v); //���������� ����Ʈ���� �ش� ��ü ����
			if(v instanceof Member) {members.remove(v);} //���� ȸ���̶��, ȸ����ܿ����� ���� 
			System.out.println("���� �湮�� ��: "+visitors.size());		
		}		
	}
	
public boolean borrowMaterial(Visitor v, String ti){ //�湮�� V�� ti��� �ڷḦ ���Ҷ� 
		//�켱 ������ material �� � �ִ��� ã�ƺ��� �뿩������ material �� ������ �����Ѵ�.
		int avail=0, using = 0;
		//avail�� ���������� �뿩�� ������ �ڷ��� ��  , using�� ���� �뿩�� �Ұ����ϸ� �ٸ������ �аų� �뿩�� ��
		if(v.hands.size() >= v.borrowLimit){ //���� �湮���� �վ� ����ִ� material�� �ʰ� �����̸� 
			System.out.println(v.name+"��(��) ���̻� ���� �� �����ϴ�.");
			return false; //�ϴ� �ʰ������� �뿩�ѻ���� �����Ѵ�.
		}
			
		for (Material im : materials){
		if(im.title.equals(ti))
		{ //�湮���� ���ϴ� �ڷᰡ �ִ� �� Ž��
			if(im instanceof NewsPaper) {	System.out.println("�Ź� �ڷ�� ���� �� ���� " + v.name+" �� ���� ��û�� �����մϴ�"); return false;	}		
			if(im.state == Material.AVAILABLE || im.state == Material.BORROW_ONLY) {avail++;}
			else if(im.state == Material.BORROWED || im.state == Material.READING) {using++;}
			
			//���⼭ avail�� �湮���� ���ϴ� �ڷᰡ ������ ��, using �湮���� �������� ���� �뿩/�д� �ڷ��� ��
		}	

		}
		
		if(avail >0)
		{//���� �ڷᰡ 1���̻��̶�� �뿩 ������ ��´�.
			for (Material im : materials)
			{//�ش� �ڷḦ �ٽ� for each������ ���Ͽ� ã�´�.
				if(im.title.equals(ti) && (im.state==Material.AVAILABLE || im.state ==Material.BORROW_ONLY) ){ //���� merterial�� AVAILABLE�̸� 
					v.hands.add(im); //�湮���� ����ǰ �迭�� �ִ´�.
					System.out.println(v.name+"���� �ڷ� \""+ti+"\" (ISBN: "+im.ID+") ��(��) ���� �մϴ�"+"[���� �뿩/�б� ��:"+(v.hands.size())+"]");	//v���� �ڷḦ �뿩�Ѵ�.			
					im.isBorrowed(); //�׸��� �� �ڷḦ Borrowed �� �Ѵ�.
					return true; }
					
			}	
		}
		else
		{ //���� ������ ������ �ڷᰡ ���ٸ� , using =0�̶�� �� �ڷ�� �������� �ڷ��. ���� using�� 1���� ũ�� ���� �ٸ������ �뿩�����ڷ�
			if(using ==0){	System.out.println("�ڷ� \""+ti+"\" �� ���� "+v.name+"�� ���� ��û�� �����մϴ�"); return false; }
			else {	System.out.println("\""+ti+"\"�ڷᰡ �뿩[�б�]�� �̹Ƿ�" + v.name+" �� ���� ��û�� �����մϴ�"); 	return false; }
		}
	

return false;
}
	


public boolean readMaterial(Visitor v, String ti){
		for (Material im : materials){//for-each���� �̿��Ͽ� ti��� �ڷḦ ã�´�.
			if(im.title.equals(ti)){//���� ti��� �ڷ�� ������ �ڷᰡ ������
				if(im.state==Material.AVAILABLE || im.state==Material.READ_ONLY){
					v.hands.add(im); //�湮���� ����ǰ�� �߰�
					System.out.println(v.name+" ��(��) �ڷ� \""+ti+"\" ��(��) �����մϴ�");
					im.isRead();//�ڷḦ �������·� ����
					return true;
				}
				else
				{
					System.out.println("�ڷ� \""+ti+"\"�� ������ �� �����ϴ�");
					return false;
				}
			}			
		}
		System.out.println("�ڷ� \""+ti+"\" �� ���� "+v.name+"�� ������û�� �����մϴ�");
		return false;
	}
	
public void returnMaterial(Visitor v, Material m){
		for(Material im : v.hands){//�ڷḦ ��ȯ�ϴ� �޼ҵ� ��ȯ�޼ҵ� Ž��
			if (im.equals(m)){//���� �ڷ�� ��ȯ�ڷᰡ �����ϸ�
				System.out.println(v.name+"��(��) \""+im.title + "\" (ISBN:" + im.ID + ")��(��) �ݳ��մϴ�. ���� �뿩/�б�: "+v.hands.size()+"(��)");
				v.hands.remove(im);//�湮���� ����ǰ���� ����
				im.isReturned();//�ڷḦ available read_only�� ����
				return;
			}
		}
		System.out.println("[�ݳ�����] "+m.title+" �ݳ��� ������ �������� �ʽ��ϴ�!");
		return;				
	}
	
public void returnMaterial(Visitor v, String ti) //���� ������ �Լ����� , ���ڰ� �ٸ� �������̵� �Ǿ��ִ�. 
	{
		for(Material im : v.hands) //for each���� Ž���Ͽ� ����ڰ� ��ȯ�ϰ����ϴ� �ڷḦ ã�´�.
		{
			if (im.title.equals(ti))
			{
				v.hands.remove(im); //������
				System.out.println(v.name+"��(��) \""+im.title + "\" (ISBN:" + im.ID + ")��(��) �ݳ��մϴ�. ���� �뿩: "+v.hands.size()+"(��)");
				im.isReturned();//�ش��ڷḦ �����Ѵ�.
				return;
			}
		
		}
		
		System.out.println("[�ݳ�����] "+ti+" �� �������� �ʽ��ϴ�!");
		return;				
	
	}

public void showLibraryStatus() //���� ������ ���¸� üũ�Ѵ�.
{
	System.out.println("-------------------------------------------------------------------------------------");
	System.out.println("������ �̿���: "+visitors.size()+" �� �Դϴ�."+"ȸ��: "+ members.size() +" �� "+" ��ȸ�� "+(visitors.size()-members.size())+" ��");
	//����Ʈ�� Ȯ���Ͽ�, ���� ȸ���� ���� ��ȸ���� ���� ��Ÿ����. visitor.size()�޼ҵ�� �̸� ������ش�.
	for(Visitor vi: visitors)
	{
		//���������� �湮�� ����Ʈ visitors�� �����Ͽ� ��� ����� ����ǰ (�뿩/�б�)�� Ȯ���ϴ�.
		System.out.print(vi.name+" ���� �뿩 ����: ");
		for(Material ma :vi.hands) 
		{
		System.out.print(ma.title+" |");
		}
		System.out.println("");
	}

	System.out.println("-------------------------------------------------------------------------------------");
}

	

}
