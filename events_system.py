
# Lista de diccionarios que contienen como key al evento (string)
# y como value a las funciones que se llaman ante ese evento.


events = {
    "medicion_alta": [fn1(), fn2()],
    "boton_presionado": function_boton_presionado()

}

def register_event(event: str, function: callable):
    handlers = events.get(event)    # handlers posee la lista de funciones de

    if handlers is None:
        events[event] = [function]
    else:
        handlers.append(function)

def dispatch()