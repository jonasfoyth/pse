#include "Telegram.h"

Erro criarStruct(Telegram* telegram,  Telegram_id id, float data) {
	if (data <= 0.0 || data >= 0.0) {
		telegram->id = id;
		telegram->data.temperature = data;
		return ERRO_OK;
	}

	return ERRO_VALOR_INVALIDO;
}
