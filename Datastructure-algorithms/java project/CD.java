
public class CD extends Material {	
	static int total_cd=1; //cd �� ������ �����Ѵ�. �� ������ ������ ���̵�� ���ȴ�.
	public CD() {
		super();//super���� Material�� �����ڸ� ȣ���Ѵ�.
		state =UNCLASSIFIED; //���� CD�� �̸��� �������� ������, ����/�����Ұ����°� �ȴ�. 
	}
	public CD(String title, String author) {
		super(title,author);//super���� Material�� �����ڸ� ȣ���Ѵ�.
		state = BORROW_ONLY; //cd�� ������ �õ�� �뿩���ɻ��·� �ٲ��.
		ID="C"+ total_cd++;
	}
	public CD(String title) {
		super(title);//super���� Material�� �����ڸ� ȣ���Ѵ�.
		state = BORROW_ONLY;
		ID="C"+ total_cd++;// �õ��� c + ������ Ű���� id�̴�.
	}
	
	@Override
	public void isBorrowed() {
		if(state ==BORROW_ONLY) //cd �� �뿩���� �����̸�, cd�� �뿩�� �����ϹǷ�
		state = BORROWED;//�뿩�Ѵ�.
	}

	@Override
	public void isReturned() {
		if(state != BORROW_ONLY)
		state = BORROW_ONLY;
	}
	@Override
	public void isRead(){
		
	}
	

}
