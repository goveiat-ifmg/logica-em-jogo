import google.generativeai as genai
import os
import sys

# Configura o caminho do arquivo de log
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_PATH = os.path.join(SCRIPT_DIR, "gemini_bridge_log.txt")


# Função para registrar mensagens de log, isto é, mensagens recebidas do C e do Gemini
def registrar_no_log(mensagem):
    with open(LOG_PATH, "a") as log_file:
        log_file.write(mensagem + "\n")


try:
    # 1. Configura a API Key a partir da Variável de Ambiente
    genai.configure(api_key=os.getenv("GEMINI_API_KEY"))


    # 2. Inicializa o modelo
    model = genai.GenerativeModel('gemini-2.5-flash')


    # 3. Pega o prompt que o C enviou (via argumento de linha de comando)
    if len(sys.argv) > 1:
        prompt_do_c = sys.argv[1]
        registrar_no_log(f"Prompt recebido do C: {prompt_do_c}")
    else:
        raise ValueError("Nenhum prompt fornecido pelo C.")


    # 4. Envia o prompt para a API e recebe a resposta
    response = model.generate_content(prompt_do_c)
    registrar_no_log(f"Resposta recebida do Gemini: {response.text}")


    # 5. Imprime a resposta para o C poder ler
    # Remove quebras de linha da resposta da IA para facilitar a leitura
    print(response.text.strip())


except Exception as e:
    # Se algo der errado (ex: API Key errada), informa o C
    registrar_no_log(f"ERRO;{str(e)}")
