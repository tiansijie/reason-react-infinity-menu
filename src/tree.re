type node =
  Js.t {
    .
    name : string,
    id : string,
    isOpen : option string,
    children : option (array node)
  };
