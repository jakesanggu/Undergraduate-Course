
public class NonMember extends Visitor {

	public NonMember(String na, int ag) {
		super(na, ag);
		borrowLimit=3;//��ȸ���� �ִ� ���Ⱑ�ɼ��� 3���̴�. ������ �ʱ�ȭ�� �ڵ����� ���� �ʵ� borrowLimit�� ���� ���Եȴ�.
		
	}

	@Override
	public boolean isMember() {
		return false; //��ȸ���� false�� ��ȯ�Ѵ�.
	}

}
