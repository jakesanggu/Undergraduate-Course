public class SearchGate {
	
	public boolean search(Visitor v){
	for(Material im : v.hands) //�湮���� �뿩���� ���� �ڷḦ ������ ������ Ž��
	{
		if(im.state != Material.BORROWED && !(im instanceof Ebook)) //���� STATE�� BORROWED�� �ƴ϶��, ������ BORROWED�� �ڷḸ ��� ���� �� �ִ�.
		{ //EBOOK�� �׳� ������ ���� �� �ִ�.
			System.out.println("[�߻߻�] ������ ����! " + v.name + "�� ���� �뿩���� �ʴ� å "+im.title +" �� �����մϴ�.");
			return false;//�����°��� �����Ѵ�.
		}
	}
		
		return true;//�����°� ���
	}
	
	
	public boolean enter(Visitor v) //�������� ����� ����ȸ������ �Ǻ�
	{
		if(Library.blcokmember.contains(v)) {//����ȸ�� ����Ʈ�� �湮���� ��ü�� �ִٸ�
			System.out.println("[�߻߻�]"+v.name+"�� �̳��Ͻ� ��ü ����� ���� �繫�ҿ��� �������ּ���");
			return false;//����ź�
		}
		
		else
		return true;
	}
	
}
