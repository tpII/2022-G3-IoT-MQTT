
# Lista de diccionarios que contienen como key al evento (string)
# y como value a las funciones que se llaman ante ese evento.
events = {}


def register_event(event: str, function: callable):
    # Registra un evento, para su posterior dispatch

    handlers = events.get(event)    # handlers posee la lista de funciones consumidoras

    if handlers is None:
        events[event] = [function]
    else:
        handlers.append(function)


def dispatch(event: str, data):
    # Invoca a los controladores/manejadores del evento asociado

    handlers = events.get(event)
    
    if handlers is None:
        raise ValueError(f"El evento '{event}' no ha sido encontrado.")
    else:
        for handler in handlers:
            handler(data)