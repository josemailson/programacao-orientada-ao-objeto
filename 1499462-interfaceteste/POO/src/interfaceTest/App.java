package interfaceTest;

public class App{
	public static void main(String[] args) {
		Funcionario f1= new Funcionario("Maria");
		//f1.setNome("jose");
		
		f1.recebeSalario();
		Gerente g1 = new Gerente();
		g1.recebeSalario();
		Diretor d1 = new Diretor();
		d1.recebeSalario();
		
		Autenticavel[] autenticadores = new Autenticavel[2];
		autenticadores[0] = g1;
		autenticadores[1] = d1;
		
		for (Autenticavel a : autenticadores) {
			a.autentica();
		}
		
		d1.demite(f1);
	}
}
