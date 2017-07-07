var path = require("path");

module.exports = {
  entry: "./tests/index.js",
  output: {
    path: path.resolve(__dirname, "tests/compiled"),
    filename: "[name].js"
  },
  module: {
      rules: [
       {
         test: /\.js$/,
         exclude: /(node_modules)/,
         use: {
           loader: "babel-loader",
           options: {
             presets: ["env", "react"]
           }
         }
       }
      ]
  }
};
