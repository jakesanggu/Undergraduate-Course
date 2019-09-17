public class Book extends Material {
	
	static int total_books=1; //�� å�� ������ �����Ѵ�. �� ������ ������ ���̵�� ���ȴ�.
	
	public Book(String ti){
		super(ti); //super���� Material�� �����ڸ� ȣ���Ѵ�.
		state = AVAILABLE;//å�� ������ ����/�뿩�������ѻ��·� ����
		ID="B"+ total_books++; //å ������ ���̵�� å(B)�� �����ϸ� �ڿ��� ��ϵ� ������ ��ȣ�̴�.
	}
	public Book(String ti, String author){
		super(ti,author);//super���� Material�� �����ڸ� ȣ���Ѵ�.
		state = AVAILABLE; //å�� ������ ����/�뿩�������ѻ��·� ����
		ID="B"+ total_books++;  //å ������ ���̵�� å(B)�� �����ϸ� �ڿ��� ��ϵ� ������ ��ȣ�̴�.
	}
	public Book(){
		super();//super���� Material�� �����ڸ� ȣ���Ѵ�.
		state =UNCLASSIFIED; //���� å�� �̸��� �������� ������, ����/�����Ұ����°� �ȴ�. 
	}

	@Override
	public void isBorrowed() {
		if(state ==AVAILABLE)
		state = BORROWED; //���� å�� �뿩/������ ������ ���¸� �̸� �뿩���·� ��ȯ
	}

	@Override
	public void isReturned() {
		if(state != AVAILABLE) //�ݳ��� ��� Borrowed Ȥ�� Reading�̹Ƿ� ���߿� �ƴ϶��
		state = AVAILABLE;
	}
	@Override
	public void isRead(){
		if(state == AVAILABLE)
		state = READING; //å�� �б� ���ؼ��� available �����̾���Ѵ�. �̸� READING ���·� ����
	}
	
}
