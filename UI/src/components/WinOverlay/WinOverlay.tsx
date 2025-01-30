import { Link } from "react-router-dom";
import "./WinOverlay.css";


/**
 * @interface WinOverlayProps
 * @brief Propriedades do componente WinOverlay.
 * @property {string} winnerplayer Nome do jogador vencedor.
 * @property {string} wintype Tipo de vitória (ex: "win", "tie").
 * @property {(arg0: boolean) => void} reset Função para reiniciar o jogo.
 * @property {string} [className] Classe CSS adicional para personalização.
 */
interface WinOverlayProps{
    winnerplayer:string;
    wintype:string;
    reset: (arg0:boolean)=>void;
    className?:string;
}


/**
 * @brief Componente que exibe uma sobreposição de vitória/empate.
 * @param {WinOverlayProps} props Propriedades do componente.
 * @return {JSX.Element} Retorna o componente de sobreposição de vitória/empate.
 */
export const WinOverlay = ({winnerplayer, wintype, reset, className}:WinOverlayProps) => {

    /**
     * @brief Lida com a solicitação para jogar novamente.
     * @details Chama a função `reset` para reiniciar o jogo.
     */
    const handleRetryRequest = () => {
        reset(true);
    }

    return (
        <div className={"winoverlaybody "+className}>
            <button className="retrybutton" onClick={()=>handleRetryRequest()}>
                <h1 className="retrytext">{"Jogar novamente >"}</h1>
            </button>
            <Link to={"/"}>
                <button className="menubutton">
                    <h1 className="menutext">{"< Selecionar jogadores"}</h1>
                </button>
            </Link>
            <h2 style={{marginTop:"-58vh"}}>{wintype==="tie"? "Empate!" : (winnerplayer + " venceu!")}</h2>
        </div>
    )
}