
public abstract class Material {
	String title;  
	String author;
	String ID; //���� �νĹ�ȣ å�̸� b1 ~ b .... �Ź��̸�, n1  ~ n...
	int state; 	
	
	public static int AVAILABLE = 0;
	public static int READING = 1;
	public static int BORROWED = 2;
	public static int READ_ONLY = 3;	
	public static int BORROW_ONLY = 4;
	public static int UNCLASSIFIED =5;//Ȯ���� �� ���� ��ü�϶� 

	public Material(){
		title = "Unkown";
		author= "Unkown";//�����ڳ��� ���ڰ� ���޵��� ������, Ȯ���� �� ���� ��ü�̴�. ��
	}
	public Material(String ti){
		title = ti; //ti�� ��ü title�� ����
		author = "Unkown";
	}
	public Material(String ti,String au){
		title = ti;
		author= au;
	}

	public abstract void isReturned(); // �ݳ� �� ���� ��ȭ �Լ�
	public abstract void isBorrowed(); // �뿩 �� ���� ��ȭ�Լ�
	public abstract void isRead(); // �б� �� ���º�ȭ
	


}
