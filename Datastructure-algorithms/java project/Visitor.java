import java.util.ArrayList;

public abstract class Visitor {
	String name; 
	int age;	
	int borrowLimit;
	static int count=1;//�湮���� �� �� �̴�.
	
	ArrayList<Material> hands = new ArrayList<Material>(); // ������ ������ arrayList�� ���Ͽ� �����Ͽ���
	
	public Visitor(String na, int ag){
		name=na; age=ag;
	}
	
	public abstract boolean isMember();//�ɹ����� Ȯ���ϴ� �߻� �޼ҵ�
}
