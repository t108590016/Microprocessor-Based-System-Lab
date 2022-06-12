const express = require("express")
const app = express();

app.use(express.static('./public'));


app.get("/control", (req,res)=>{
	controlLED(req.query.LED1, req.query.control)
	controlLED(req.query.LED2, req.query.control)
	controlLED(req.query.LED3, req.query.control)
	controlLED(req.query.LED4, req.query.control)
	var response = {
		"LED1": req.query.LED1,
		"LED2": req.query.LED2,
		"LED3": req.query.LED3,
		"LED4": req.query.LED4,
		"Control": req.query.control,
	}
	res.send("Successfully Requested")
})

app.get("/switching", (req,res)=>{
	controlLED("Mode_Shine", req.query.times)
	res.send("Successfully Requested")
})

function controlLED(LED, POWER){
	let child_process = require("child_process");
	let process = child_process.execFile('sudo', ["./C++/L2Program", LED, POWER
]);
	process.stdout.on('data', (data) => {
	console.log('stdout: ${data}');
});
	process.stderr.on('data', (data) => {
	console.error('stderr: ${data}');
})


}

const PORT = process.env.PORT || 8080;
app.listen(PORT, ()=>{
	console.log('Server is running on port ${PORT}');	
});
