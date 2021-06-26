package interfaceTest;

public class Gerente extends Funcionario implements Autenticavel{

	void recebeSalario() {
		System.out.println("gerente recebendo salario");
	}

	@Override
	public void autentica() {
		System.out.println("gerente autenticando...");
		
	}
}
