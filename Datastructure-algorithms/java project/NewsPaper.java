
public class NewsPaper extends Material {

	static int total_newspaper=1;
	
	public NewsPaper() {
		super();
		state = UNCLASSIFIED; //������ ���ں����� �˼����� �ڷ�� ����
	}
	public NewsPaper(String title, String author) {
		super(title,author);
		state = READ_ONLY;
		ID="N"+ total_newspaper++; //��� �����ϰ� N + �Ź� ����Ű�� �Ѵ�. ������ ȣ��� �ڵ����� Ŭ�������� TOTAL_NEWSPAPAER�� ���� ����
	}
	public NewsPaper(String title) {
		super(title);
		state = READ_ONLY;
		ID="N"+ total_newspaper++;
	}
	
	
	
	@Override
	public void isBorrowed() {
	//�Ź��� �������� �����Ƿ� state�� �ٲ��� �ʴ´�.
	}

	@Override
	public void isReturned() {
		if(state != READ_ONLY)
		state = READ_ONLY; //�Ź��� �б⸸ �����ϹǷ�, ��ȯ�� �׻� Read_only�� �ٲپ��ش�.
	}
	@Override
	public void isRead(){
		
		if(state == READ_ONLY) //�Ź��� Read_only -> Reading���� �ΰ��� ���¸� �����ϴ�.
		state = READING;
		
	}
	

}
