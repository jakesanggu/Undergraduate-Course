
public class Member extends Visitor {
	
	String ID;//�湮���� ������ȣ
	public Member(String na, int ag){
		super(na, ag);
		borrowLimit=5;//�ɹ��ǰ�� 5���� �������ִ�
		ID="M"+count++; //�湮���� ������ȣ�� "M"��� + ���� �ο� conut�� ������ �߰����ش�. �� �����ڰ� ȣ��Ǹ� count�� ������Ų��.
		
	}

	public boolean isMember(){
		//������ ������� Ȯ���ϴ� �޼ҵ�� ����� ������ true �ƴϸ� false�� ��ȯ�Ѵ�.
		
		return true;
	}
}
