package interfaceTest;

public class Funcionario {

	private String nome;
	
	public Funcionario(String nome) {
		this.nome = nome;
	}
	
	public Funcionario() {
		super();
	}
	
	void recebeSalario() {
		System.out.println("recebendo salario");
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}
	
}
