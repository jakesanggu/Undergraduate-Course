
public class Ebook extends Material {

	static int total_ebooks=1;
	/*Ebook Material �� �ڷḦ �ٿ� �ޱ� ������ ������ �����ϴ�.
	 * 
	 * 1. ���ÿ� �ڷḦ ������ �� �ִ�. 
	 * 2. �뿩��� ������ �ʿ����.
	 * 3. �� �ٸ� �ڷ�� ����ϰ� ���� ������ �����Ѵ�.
	*/
	
	public Ebook(String ti , String author)
	{
		super(ti,author);
		state = AVAILABLE; //ebook�� å�������ϴ�. ���������̴�. �� ���´� �׻� ���������̴�.
		ID="E"+ total_ebooks++; //ebook�� ���� id�� ���������� �����Ѵ�.
	}
	public Ebook(String ti)
	{
		super(ti);
		state = AVAILABLE;
		ID="E"+ total_ebooks++;
	}
	public Ebook() {
		super();
		state = UNCLASSIFIED;
	}
	
	
	@Override
	public void isReturned() {
	//ebook�� ��� state�� ������ ���� �ʴ´�.
		
	}

	@Override
	public void isBorrowed() {
		//ebook�� ��� state�� ������ ���� �ʴ´�.
	}

	@Override
	public void isRead() {
		//ebook�� ��� state�� ������ ���� �ʴ´�.
		
	}

}
