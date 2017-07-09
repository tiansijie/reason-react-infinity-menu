type tree = array Tree.node;

let component = ReasonReact.statelessComponent "InfinityMenu";

let make tree::(tree: tree) _children => {
  let rec convertTreeToDiv (node: Tree.node) (keyPath: string) (level: int) => {
    let id = node##id;
    let newLevel = level + 1;
    switch (Js.Null_undefined.to_opt node##children) {
    | Some children =>
      children |>
      Js.Array.reducei
        (
          fun prev (child: Tree.node) index => {
            let accu =
              prev |>
              Js.Array.concat (
                convertTreeToDiv child {j|$keyPath.children.$index|j} newLevel
              );
            accu
          }
        )
        [||]
    | None => [|
        <li key={j|$keyPath+$id|j}>
          (ReasonReact.stringToElement node##name)
        </li>
      |]
    }
  };
  let convertTree (tree: tree) => {
    let results =
      tree |>
      Js.Array.reducei
        (
          fun accu (node: Tree.node) index =>
            accu |>
            Array.append (convertTreeToDiv node (string_of_int index) 0)
        )
        [||];
    ReasonReact.arrayToElement results
  };
  {
    ...component,
    render: fun _self => {
      let displayTree = convertTree tree;
      <div> displayTree </div>
    }
  }
};

let jsComponent =
  ReasonReact.wrapReasonForJs
    ::component (fun jsProps => make tree::jsProps##tree [||]);
